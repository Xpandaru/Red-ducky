#include <stdio.h>
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "layout.h"
#include "parser.h"
#include "cdc_input.h"
#include "script_storage.h"

#define MAX_SCRIPT_LINES 200

typedef enum {
    TYPE_IDLE,
    TYPE_PRESS,
    TYPE_RELEASE
} type_state_t;

typedef enum {
    MODE_ACTIVE,
    MODE_EDIT,
    MODE_WRITING,
    MODE_ERROR
} SystemMode;

// Variables declaration

static SystemMode system_mode = MODE_ACTIVE;
static char cdc_line_buffer[1009];
static int cdc_error = 0;
static int show_line_count = 0;
static int write_line_count = 0;

static int script_length = 0;
static bool script_done = false;

static int global_delay = 0;

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

        case CMD_GBDELAY:
            global_delay = cmd->value;
            break;

        case CMD_MODIFIER:
            if (cmd->keycode != 0) {
                forced_keycode = cmd->keycode;
                forced_modifier = cmd->modifier;
                is_forced = true;
                typing_done = false;
            }
            else printf("ERROR(5): Argument not found : %s - %s\n\n", cmd->modifier, cmd->keycode);
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
            system_mode = MODE_ERROR;
            printf("ERROR(4): Command not found or wrong argument type : %s\n\n", cmd->argument);
            break;
    }
}

int main() {
    stdio_init_all();
    board_init();
    tusb_init();

    // LED variables

    const uint LED_PIN = 25;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    absolute_time_t blink_delay = get_absolute_time();
    bool led_state = false;

    while (!tud_hid_ready()) {
        tud_task();
    }

    static char* script[MAX_SCRIPT_LINES];

    if (script_is_present()) {
        script_length = script_load(script, MAX_SCRIPT_LINES);
    }
    else system_mode = MODE_EDIT;
    
    int current_line = 0;

    Command cmd;
    delay_until = get_absolute_time();

    while (true) {
        tud_task();
        hid_type_task();

        switch (system_mode) {

        case MODE_ACTIVE:
            gpio_put(LED_PIN, !script_done);
            led_state = !script_done;
            break;
        
        case MODE_EDIT:
        case MODE_WRITING:
            if (time_reached(blink_delay)) {
                led_state = !led_state;
                gpio_put(LED_PIN, led_state);
                blink_delay = make_timeout_time_ms(500);
            }
            break;

        case MODE_ERROR:
            if (time_reached(blink_delay)) {
                led_state = !led_state;
                gpio_put(LED_PIN, led_state);
                if (led_state) blink_delay = make_timeout_time_ms(100);
                else blink_delay = make_timeout_time_ms(200);
            }
            break;
        
        default:
            break;
        }

        if (tud_cdc_available()) {
            
            if (cdc_read_line(cdc_line_buffer, sizeof(cdc_line_buffer), &cdc_error)) {

                if (cdc_error == 1) {
                    printf("ERROR(1): Buffer overflow : Your last entry exceeded the supported character limit.\n\n");
                }

                if (cdc_error == 2) {
                    printf("ERROR(2): Buffer overflow : Your last entry exceeded the supported character limit.\n\n");
                }

                if (strcmp(cdc_line_buffer, "EDIT START") == 0) {

                    printf("----------{EDIT MODE ENABLED}----------"
                        "\nTo quit this mode, type : EDIT QUIT"
                        "\n\nCommands :"
                        "\n- SCRIPT EDIT : start editing the current script"
                        "\n- SCRIPT BEGIN : remove the current script to create a new script, all commands after it are saved as the new script until SCRIPT END."
                        "\n- SCRIPT END : marks the end of a script block and save it as the new script."
                        "\n- SCRIPT DEL : delete the last line of the script."
                        "\n- SCRIPT SHOW : show the current saved script."
                        "\n\n"
                    );
                    system_mode = MODE_EDIT;
                }

                if (strcmp(cdc_line_buffer, "EDIT QUIT") == 0 && system_mode != MODE_WRITING) {

                    printf("---------{EDIT MODE DISABLED}----------\n\n");
                    system_mode = MODE_ACTIVE;
                }

                if (strcmp(cdc_line_buffer, "EDIT QUIT") == 0 && system_mode == MODE_WRITING) {
                    printf("You cannot quit the EDIT MODE while editing the script. To quit the EDIT MODE, first type SCRIPT END.\n\n");
                }

                if (system_mode == MODE_EDIT) {

                    if (strcmp(cdc_line_buffer, "SCRIPT BEGIN") == 0) {
                        printf("Each new entry will be treated as a new line of the script. To exit this mode, type SCRIPT END.\n\n");
                        script[0] = NULL;
                        write_line_count = 0;
                        system_mode = MODE_WRITING;
                    }

                    if (strcmp(cdc_line_buffer, "SCRIPT EDIT") == 0) {

                        printf("---------------{SCRIPT}----------------\n");
                        show_line_count = 0;
                        while (script[show_line_count] != NULL) {
                            printf("%s\n", script[show_line_count++]);
                        }
                        printf("\nType SCRIPT END to save the script.\n\n");

                        write_line_count = script_length;
                        system_mode = MODE_WRITING;
                    }

                    else if (strcmp(cdc_line_buffer, "SCRIPT END") == 0) {
                        printf("You cannot finish a script that has not started. To start a script, type SCRIPT BEGIN.\n\n");
                    }

                    else if (strcmp(cdc_line_buffer, "SCRIPT DEL") == 0) {
                        printf("This command is only accessible when editing or writing a script. To start editing a script, type SCRIPT EDIT, or to start a script, type SCRIPT EDIT.\n\n");
                    }

                    else if (strcmp(cdc_line_buffer, "SCRIPT SHOW") == 0) {
                        printf("---------------{SCRIPT}----------------\n");

                        show_line_count = 0;
                        while (script[show_line_count] != NULL) {
                            printf("%s\n", script[show_line_count++]);
                        }
                        printf("\n");
                    }
                }
                else if (system_mode == MODE_WRITING) {

                    if (strcmp(cdc_line_buffer, "SCRIPT END") == 0) {
                        if (script_save(script)) printf("Script saved successfully !\n\n");
                        else printf("ERROR(3): Flash overflow : The script size exceeds the allocated space in the flash memory.\n\n");
                        system_mode = MODE_EDIT;
                    }

                    else if (strcmp(cdc_line_buffer, "SCRIPT DEL") == 0) {
                        write_line_count--;
                        script[write_line_count] = NULL;

                        printf("---------------{SCRIPT}----------------\n");
                        show_line_count = 0;
                        while (script[show_line_count] != NULL) {
                            printf("%s\n", script[show_line_count++]);
                        }
                        printf("\nType SCRIPT END to save the script.\n\n");
                    }

                    else {
                        script[write_line_count++] = strdup(cdc_line_buffer);
                        script[write_line_count] = NULL;

                        printf("---------------{SCRIPT}----------------\n");
                        show_line_count = 0;
                        while (script[show_line_count] != NULL) {
                            printf("%s\n", script[show_line_count++]);
                        }
                        printf("\nType SCRIPT END to save the script.\n\n");
                        
                    }
                }
            }
        }

        if ((script[current_line] == NULL && typing_done) || system_mode != MODE_ACTIVE) script_done = true;

        if (typing_done && time_reached(delay_until) && script[current_line] != NULL && !script_done) {
            
            cmd = parse_line(script[current_line]);
            execute_command(&cmd);

            if (cmd.type != CMD_DELAY && cmd.type != CMD_REPEAT && cmd.type != CMD_REM && cmd.type != CMD_GBDELAY) delay_until = make_timeout_time_ms(global_delay);

            if (repeat <= 0 || cmd.type == CMD_REPEAT) {
                current_line++;
            }

            if (repeat > 0) repeat--;
            
        }
    }
}
