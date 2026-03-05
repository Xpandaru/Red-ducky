#ifndef LAYOUT_H 
#define LAYOUT_H

#include <stdint.h>

extern bool is_azerty;

uint8_t layout_get_keycode(char c, uint8_t* modifier);

#endif
