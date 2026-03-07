#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef enum {
    CMD_NULL,
    CMD_LAYOUT,
    CMD_REM,
    CMD_REPEAT,
    CMD_STRING,
    CMD_DELAY,
    CMD_GBDELAY,
    CMD_MODIFIER,
    CMD_KEY,
} CommandType;

typedef struct {
    CommandType type;
    char argument[1002];
    uint8_t modifier;
    uint8_t keycode;
    int value;
} Command;

Command parse_line(const char* line);

#endif
