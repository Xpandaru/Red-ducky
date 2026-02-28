#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef enum {
    CMD_NULL,
    CMD_STRING,
    CMD_DELAY,
    CMD_ENTER,
    CMD_MODIFIER,
    CMD_KEY,
} CommandType;

typedef struct {
    CommandType type;
    char argument[128];
    uint8_t modifier;
    uint8_t keycode;
    int value;
} Command;

Command parse_line(const char* line);

#endif
