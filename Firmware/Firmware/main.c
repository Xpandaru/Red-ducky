#include <stdio.h>
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "layout.h"
#include "parser.h"

typedef enum {
    TYPE_IDLE,
    TYPE_PRESS,
    TYPE_RELEASE
} type_state_t;

// Variables declaration

static bool script_done = false;

static const int global_delay = 1000;

static type_state_t type_state = TYPE_IDLE;
static const char* current_text = NULL;
static int current_index = 0;
static bool typing_done = true;

static bool is_forced = false;
static uint8_t forced_keycode = 0;
static uint8_t forced_modifier = 0;

static  int repeat = 0;

static absolute_time_t next_event_time;
static absolute_time_t delay_until;

// Functions declaration

void hid_press(uint8_t keycode, uint8_t modifier) {
    uint8_t keys[6] = {0};
    keys[0] = keycode;
    tud_hid_keyboard_report(0, modifier, keys);
}

void hid_release(void) {
    uint8_t empty[6] = {0};
    tud_hid_keyboard_report(0, 0, empty);
}

void start_typing(const char* text) {
    current_text = text;
    current_index = 0;
    type_state = TYPE_IDLE;
    typing_done = false;
    next_event_time = get_absolute_time();
}

void hid_type_task(void) {
    if (!tud_hid_ready()) return;
    if (typing_done) return;
    if (!time_reached(next_event_time)) return;

    static uint8_t modifier = 0;
    static uint8_t keycode = 0;

    if (!is_forced) {

        char c = current_text[current_index];

        if (c == '\0') {
            typing_done = true;
            type_state = TYPE_IDLE;
            return;
        }

        modifier = 0;
        keycode = layout_get_keycode(c, &modifier);

    }
    else {
        modifier = forced_modifier;
        keycode = forced_keycode;
    }

    // States

    switch (type_state) {
        case TYPE_IDLE:
            hid_press(keycode, modifier);
            type_state = TYPE_PRESS;
            next_event_time = make_timeout_time_ms(10);
            break;

        case TYPE_PRESS:
            hid_release();
            type_state = TYPE_RELEASE;
            next_event_time = make_timeout_time_ms(10);
            break;

        case TYPE_RELEASE:
            if (is_forced) {
                is_forced = false;
                typing_done = true;
            }
            else {
                current_index++;
            }
            type_state = TYPE_IDLE;
            next_event_time = make_timeout_time_ms(10);
            break;
    }
}

void execute_command(Command* cmd) {
    switch (cmd->type) {

        case CMD_REM:
            break;

        case CMD_LAYOUT:
            if (strcmp(cmd->argument, "AZERTY") == 0) is_azerty = true;
            if (strcmp(cmd->argument, "QWERTY") == 0) is_azerty = false;
            break;

        case CMD_REPEAT:
            repeat = cmd->value;
            break;
        
        case CMD_STRING:
            start_typing(cmd->argument);
            break;

        case CMD_DELAY:
            delay_until = make_timeout_time_ms(cmd->value);
            break;

        case CMD_MODIFIER:
            if (cmd->keycode != 0) {
                forced_keycode = cmd->keycode;
                forced_modifier = cmd->modifier;
                is_forced = true;
                typing_done = false;
            }
            break;

        case CMD_KEY:
            if (cmd->keycode != 0) {
                forced_keycode = cmd->keycode;
                forced_modifier = 0;
                is_forced = true;
                typing_done = false;
            }
            break;

        default:
            script_done = true;
            break;
    }
}

int main() {
    stdio_init_all();
    board_init();
    tusb_init();

    const uint LED_PIN = 25;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (!tud_hid_ready()) {
        tud_task();
    }

    int current_line = 0;
    static const char* const script[] = {
        "WINDOWS r",
        "STRING notepad",
        "ENTER",
        "REPEAT 5",
        "STRINGLN test",
        NULL
    };
    
    Command cmd;
    delay_until = get_absolute_time();

    while (true) {
        tud_task();
        hid_type_task();
        gpio_put(LED_PIN, !script_done);

        if (script[current_line] == NULL && typing_done) script_done = true;

        if (typing_done && time_reached(delay_until) && script[current_line] != NULL && !script_done) {
            
            cmd = parse_line(script[current_line]);
            execute_command(&cmd);

            if (cmd.type != CMD_DELAY && cmd.type != CMD_REPEAT && cmd.type != CMD_REM) delay_until = make_timeout_time_ms(global_delay);

            if (repeat <= 0 || cmd.type == CMD_REPEAT) {
                current_line++;
            }

            if (repeat > 0) repeat--;
            
        }
    }
}
