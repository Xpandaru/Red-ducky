#ifndef CDC_INPUT_H
#define CDC_INPUT_H

#include <stdbool.h>
#include <stddef.h>

void cdc_input_init(void);
bool cdc_read_line(char *out, size_t max_len, int *error);

#endif