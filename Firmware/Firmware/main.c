#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "bsp/board.h"
#include "tusb.h"

// ---------------------------------------------------------
// Flash W25Q16 GPIO pins
// ---------------------------------------------------------
#define PIN_CS    21
#define PIN_SCK   17
#define PIN_MOSI  18
#define PIN_MISO  20

// ---------------------------------------------------------
// Initialize SPI and Flash interface
// ---------------------------------------------------------
static void flash_init(void) {
    spi_init(spi0, 10 * 1000 * 1000); // 10 MHz

    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
}

// ---------------------------------------------------------
// Read JEDEC ID from W25Q16
// ---------------------------------------------------------
static bool flash_read_jedec_id(uint8_t *man, uint8_t *type, uint8_t *cap) {
    uint8_t cmd = 0x9F;
    uint8_t id[3] = {0};

    gpio_put(PIN_CS, 0);
    spi_write_read_blocking(spi0, &cmd, id, 3);
    gpio_put(PIN_CS, 1);

    *man  = id[0];
    *type = id[1];
    *cap  = id[2];

    return (id[0] == 0xEF); // Expected Winbond manufacturer ID
}

// ---------------------------------------------------------
// Read a single line from flash memory
// addr = current script address
// returns false when encountering 0x00 (end of script)
// ---------------------------------------------------------
static bool flash_read_line(uint32_t *addr, char *buffer, size_t max_len) {
    uint8_t cmd[4] = {
        0x03,                       // READ DATA command
        (*addr >> 16) & 0xFF,
        (*addr >> 8)  & 0xFF,
        *addr & 0xFF
    };

    gpio_put(PIN_CS, 0);
    spi_write_blocking(spi0, cmd, 4);

    size_t i = 0;
    while (i < max_len - 1) {
        uint8_t c = 0;
        spi_read_blocking(spi0, 0x00, &c, 1);
        (*addr)++;

        if (c == 0x00) {
            buffer[i] = '\0';
            gpio_put(PIN_CS, 1);
            return false; // End of script
        }

        if (c == '\n') {
            buffer[i] = '\0';
            gpio_put(PIN_CS, 1);
            return true;
        }

        buffer[i++] = (char)c;
    }

    buffer[i] = '\0';
    gpio_put(PIN_CS, 1);
    return true;
}

// ---------------------------------------------------------
// Send a single HID key
// ---------------------------------------------------------
static void send_key(uint8_t key) {
    uint8_t code[6] = { key, 0, 0, 0, 0, 0 };

    tud_hid_keyboard_report(0, 0, code);
    sleep_ms(50);
    tud_hid_keyboard_report(0, 0, NULL);
    sleep_ms(50);
}

// ---------------------------------------------------------
// Send a string using HID keyboard
// Basic support: A–Z, a–z, space
// ---------------------------------------------------------
static void send_string(const char *s) {
    while (*s) {
        char c = *s++;
        uint8_t keycode[6] = { 0 };
        uint8_t modifier = 0;

        if (c >= 'A' && c <= 'Z') {
            modifier   = KEYBOARD_MODIFIER_LEFTSHIFT;
            keycode[0] = HID_KEY_A + (c - 'A');
        } else if (c >= 'a' && c <= 'z') {
            keycode[0] = HID_KEY_A + (c - 'a');
        } else if (c == ' ') {
            keycode[0] = HID_KEY_SPACE;
        } else {
            // Placeholder for future punctuation support
            keycode[0] = HID_KEY_SPACE;
        }

        tud_hid_keyboard_report(0, modifier, keycode);
        sleep_ms(20);
        tud_hid_keyboard_report(0, 0, NULL);
        sleep_ms(20);
    }
}

// ---------------------------------------------------------
// Parse and execute a single Rubber Ducky script line
// ---------------------------------------------------------
static void execute_line(const char *line) {
    // Skip leading spaces
    while (*line == ' ' || *line == '\t')
        line++;

    if (*line == '\0')
        return;

    // STRING <text>
    if (strncmp(line, "STRING ", 7) == 0) {
        send_string(line + 7);
        return;
    }

    // DELAY <ms>
    if (strncmp(line, "DELAY ", 6) == 0) {
        int ms = atoi(line + 6);
        if (ms > 0)
            sleep_ms((uint32_t)ms);
        return;
    }

    // ENTER
    if (strcmp(line, "ENTER") == 0) {
        send_key(HID_KEY_ENTER);
        return;
    }

    // ESC
    if (strcmp(line, "ESC") == 0) {
        send_key(HID_KEY_ESCAPE);
        return;
    }

    // TAB
    if (strcmp(line, "TAB") == 0) {
        send_key(HID_KEY_TAB);
        return;
    }

    // Single letter A–Z / a–z
    if (strlen(line) == 1 && isalpha((unsigned char)line[0])) {
        char c = (char)toupper((unsigned char)line[0]);
        send_key(HID_KEY_A + (c - 'A'));
        return;
    }

    // Future: CTRL, ALT, GUI, combos, etc.
}

// ---------------------------------------------------------
// TinyUSB HID callbacks (required by some hosts)
// ---------------------------------------------------------
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len) {
    (void)instance;
    (void)report;
    (void)len;
}

uint16_t tud_hid_get_report_cb(uint8_t instance,
                               uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t *buffer,
                               uint16_t reqlen) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance,
                           uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const *buffer,
                           uint16_t bufsize) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;
}

// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------
int main(void) {
    stdio_init_all();
    board_init();
    tusb_init();

    flash_init();

    uint8_t man = 0, type = 0, cap = 0;
    if (!flash_read_jedec_id(&man, &type, &cap)) {
        // Flash not detected: stay idle
        while (true) {
            tud_task();
            sleep_ms(200);
        }
    }

    // Script starts at flash address 0x000000
    uint32_t addr = 0x000000;
    char line[128];

    // Main script execution loop
    while (true) {
        tud_task();

        if (!flash_read_line(&addr, line, sizeof(line))) {
            break; // End of script
        }

        // Wait until HID is ready
        while (!tud_hid_ready()) {
            tud_task();
            sleep_ms(5);
        }

        execute_line(line);
    }

    // Keep USB alive after script ends
    while (true) {
        tud_task();
        sleep_ms(50);
    }
}
