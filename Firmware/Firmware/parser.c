#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "tusb.h"

#include "parser.h"
#include "layout.h"

uint8_t get_modifier(const char* token) {
    if (strcmp(token, "CTRL") == 0)  return KEYBOARD_MODIFIER_LEFTCTRL;
    if (strcmp(token, "ALT") == 0)   return KEYBOARD_MODIFIER_LEFTALT;
    if (strcmp(token, "SHIFT") == 0) return KEYBOARD_MODIFIER_LEFTSHIFT;
    if (strcmp(token, "GUI") == 0)   return KEYBOARD_MODIFIER_LEFTGUI;
    return 0;
}


uint8_t get_keycode(const char* token) {
    if (strlen(token) == 1) {
        uint8_t modifier = 0;
        uint8_t keycode = layout_get_keycode(token[0], &modifier);
        return keycode;
    }
    if (strcmp(token, "DEL") == 0) return HID_KEY_DELETE;
    if (strcmp(token, "TAB") == 0) return HID_KEY_TAB;
    if (strcmp(token, "ESC") == 0) return HID_KEY_ESCAPE;
    if (strcmp(token, "F1") == 0) return HID_KEY_F1;
    if (strcmp(token, "F2") == 0) return HID_KEY_F2;
    if (strcmp(token, "F3") == 0) return HID_KEY_F3;
    if (strcmp(token, "F4") == 0) return HID_KEY_F4;
    if (strcmp(token, "F5") == 0) return HID_KEY_F5;
    if (strcmp(token, "F6") == 0) return HID_KEY_F6;
    if (strcmp(token, "F7") == 0) return HID_KEY_F7;
    if (strcmp(token, "F8") == 0) return HID_KEY_F8;
    if (strcmp(token, "F9") == 0) return HID_KEY_F9;
    if (strcmp(token, "F10") == 0) return HID_KEY_F10;
    if (strcmp(token, "F11") == 0) return HID_KEY_F11;
    if (strcmp(token, "F12") == 0) return HID_KEY_F12;
    return 0;
}

Command parse_line(const char* line) {

    Command cmd;
    cmd.type = CMD_NULL;
    cmd.argument[0] = '\0';
    cmd.modifier = 0;
    cmd.keycode = 0;
    cmd.value = 0;

    char buffer[128];
    strncpy(buffer, line, sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0';

    char* parsed_type = strtok(buffer, " ");

    if (parsed_type != NULL) {

        // ----------{STRING}----------

        if (strcmp(parsed_type, "STRING") == 0) {
        
            cmd.type = CMD_STRING;
            char* parsed_arg = strtok(NULL, "");

            if (parsed_arg != NULL) {
                strncpy(cmd.argument, parsed_arg, sizeof(cmd.argument));
                cmd.argument[sizeof(cmd.argument)-1] = '\0';
            }
            return cmd;
        }

        // ----------{DELAY}----------

        if (strcmp(parsed_type, "DELAY") == 0) {

            cmd.type = CMD_DELAY;
            char* parsed_arg = strtok(NULL, "");

            cmd.value = atoi(parsed_arg);

            return cmd;
        }

        // ----------{ENTER}----------

        if (strcmp(parsed_type, "ENTER") == 0) {

            cmd.type = CMD_ENTER;
            
            return cmd;
        }

        // ----------{MODIFIER}----------

        if (strcmp(parsed_type, "CTRL") == 0 ||
            strcmp(parsed_type, "ALT") == 0  ||
            strcmp(parsed_type, "SHIFT") == 0 ||
            strcmp(parsed_type, "GUI") == 0) {

            cmd.type = CMD_MODIFIER;

            cmd.modifier = get_modifier(parsed_type);

            char* token = strtok(NULL, " ");

            while (token != NULL) {

                uint8_t mod = get_modifier(token);

                if (mod != 0) {
                    cmd.modifier |= mod;
                } else {
                    cmd.keycode = get_keycode(token);

                    return cmd;
                }

                token = strtok(NULL, " ");
            }

            return cmd;
        }

        // ----------{KEY}----------

        if (strcmp(parsed_type, "DEL") == 0 ||
            strcmp(parsed_type, "TAB") == 0 ||
            strcmp(parsed_type, "ESC") == 0 ||
            strncmp(parsed_type, "F", 1) == 0) {

            cmd.type = CMD_KEY;
            cmd.keycode = get_keycode(parsed_type);
            
            return cmd;
        }


    }

    return cmd;
}
