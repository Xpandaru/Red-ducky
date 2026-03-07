#ifndef SCRIPT_STORAGE_H
#define SCRIPT_STORAGE_H

#include <stdbool.h>

bool script_is_present(void);
int script_load(char* out_script[], int max_lines);
bool script_save(char* script[]);

#endif