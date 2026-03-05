#include <stdint.h>
#include <stdbool.h>
#include "layout.h"
#include "tusb.h"

bool is_azerty = false;

uint8_t layout_get_keycode(char c, uint8_t* modifier) {

    // Uppercase management

    if (c >= 'A' && c <= 'Z') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        c = c + ('a' - 'A'); //convert to lowercase
    }

    // AZERTY conversion if activated

    if (is_azerty == true) {

        if (c == 'a') return HID_KEY_Q;
        if (c == 'z') return HID_KEY_W;
        if (c == 'q') return HID_KEY_A;
        if (c == 'm') return HID_KEY_SEMICOLON;
        if (c == 'w') return HID_KEY_Z;

        if (c >= '0' && c <= '9') *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;

        if (c == '&') return HID_KEY_1;
        if (c == '"') return HID_KEY_3;
        if (c == '\'') return HID_KEY_4;
        if (c == '(') return HID_KEY_5;
        if (c == '-') return HID_KEY_6;
        if (c == '_') return HID_KEY_8;
        if (c == ')') return HID_KEY_MINUS;
        if (c == '=') return HID_KEY_EQUAL;
        if (c == '~') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_2;
        }
        if (c == '#') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_3;
        }
        if (c == '{') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_4;
        }
        if (c == '[') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_5;
        }
        if (c == '|') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_6;
        }
        if (c == '`') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_7;
        }
        if (c == '\\') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_8;
        }
        if (c == '^') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_9;
        }
        if (c == '@') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_0;
        }
        if (c == ']') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_MINUS;
        }
        if (c == '}') {
            *modifier = KEYBOARD_MODIFIER_RIGHTALT;
            return HID_KEY_EQUAL;
        }
        if (c == '+') {
            *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
            return HID_KEY_EQUAL;
        }
        if (c == '^') return HID_KEY_BRACKET_LEFT;
        if (c == '$') return HID_KEY_BRACKET_RIGHT;
        if (c == '%') {
            *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
            return HID_KEY_APOSTROPHE;
        }
        if (c == '*') return HID_KEY_BACKSLASH;
        if (c == '<') return HID_KEY_EUROPE_2; // 0x64
        if (c == '>') {
            *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
            return HID_KEY_EUROPE_2;
        }
        if (c == ',') return HID_KEY_M;
        if (c == ';') return HID_KEY_COMMA;
        if (c == ':') return HID_KEY_PERIOD;
        if (c == '!') return HID_KEY_SLASH;
        if (c == '?') {
            *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
            return HID_KEY_M;
        }
        if (c == '.') {
            *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
            return HID_KEY_COMMA;
        }
        if (c == '/') {
            *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
            return HID_KEY_PERIOD;
        }
    }

    // QWERTY or both

    if (c >= 'a' && c <= 'z') {
        return HID_KEY_A + (c - 'a');
    }

    if (c == '`') return HID_KEY_GRAVE;
    if (c == '~') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_GRAVE;
    }
    if (c >= '1' && c <= '9') return HID_KEY_1 + (c - '1');
    if (c == '0') return HID_KEY_0;
    if (c == '!') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_1;
    }
    if (c == '@') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_2;
    }
    if (c == '#') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_3;
    }
    if (c == '$') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_4;
    }
    if (c == '%') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_5;
    }
    if (c == '^') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_6;
    }
    if (c == '&') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_7;
    }
    if (c == '*') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_8;
    }
    if (c == '(') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_9;
    }
    if (c == ')') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_0;
    }
    if (c == '-') return HID_KEY_MINUS;
    if (c == '_') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_MINUS;
    }
    if (c == '=') return HID_KEY_EQUAL;
    if (c == '+') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_EQUAL;
    }
    if (c == '[') return HID_KEY_BRACKET_LEFT;
    if (c == ']') return HID_KEY_BRACKET_RIGHT;
    if (c == '\\') return HID_KEY_BACKSLASH;
    if (c == '{') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_BRACKET_LEFT;
    }
    if (c == '}') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_BRACKET_RIGHT;
    }
    if (c == '|') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_BACKSLASH;
    }
    if (c == ';') return HID_KEY_SEMICOLON;
    if (c == '\'') return HID_KEY_APOSTROPHE;
    if (c == ':') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_SEMICOLON;
    }
    if (c == '"') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_APOSTROPHE;
    }
    if (c == ',') return HID_KEY_COMMA;
    if (c == '.') return HID_KEY_PERIOD;
    if (c == '/') return HID_KEY_SLASH;
    if (c == '<') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_COMMA;
    }
    if (c == '>') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_PERIOD;
    }
    if (c == '?') {
        *modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        return HID_KEY_SLASH;
    }

    if (c == '\n') return HID_KEY_ENTER;

    if (c == ' ') return HID_KEY_SPACE;

    return 0;
}
