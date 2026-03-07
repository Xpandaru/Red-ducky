#include "script_storage.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include <string.h>

#define SCRIPT_FLASH_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)
#define SCRIPT_FLASH_ADDR   (XIP_BASE + SCRIPT_FLASH_OFFSET)

bool script_is_present(void) {
    const uint8_t* flash = (const uint8_t*)SCRIPT_FLASH_ADDR;
    return flash[0] != 0xFF;
}

int script_load(char* out_script[], int max_lines) {
    const char* flash = (const char*)SCRIPT_FLASH_ADDR;

    if (flash[0] == (char)0xFF) {
        return 0;
    }

    int count = 0;

    while (count < max_lines) {
        if (flash[0] == '\0') {
            break;
        }

        out_script[count] = strdup(flash);
        count++;

        flash += strlen(flash) + 1;
    }

    out_script[count] = NULL;

    return count;
}

bool script_save(char* script[]) {
    uint8_t buffer[FLASH_SECTOR_SIZE];
    memset(buffer, 0xFF, sizeof(buffer));

    int pos = 0;

    for (int i = 0; script[i] != NULL; i++) {
        size_t len = strlen(script[i]);

        if (pos + len + 1 >= FLASH_SECTOR_SIZE) {
            return false;
        }

        memcpy(&buffer[pos], script[i], len);
        pos += len;
        buffer[pos++] = '\0';
    }

    if (pos < FLASH_SECTOR_SIZE) {
        buffer[pos] = '\0';
    }

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(SCRIPT_FLASH_OFFSET, FLASH_SECTOR_SIZE);

    flash_range_program(SCRIPT_FLASH_OFFSET, buffer, FLASH_SECTOR_SIZE);
    restore_interrupts(ints);

    return true;
}
