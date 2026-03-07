#include "cdc_input.h"
#include "tusb.h"

static char cdc_buffer[1009];
static size_t line_length = 0;

void cdc_input_init(void) {
    line_length = 0;
}

bool cdc_read_line(char *out, size_t max_len, int *error) {

    if (!tud_cdc_available()) {
        return false;
    }

    char c = tud_cdc_read_char();

    if (c != '\n' && c != '\r' && line_length <= sizeof(cdc_buffer) - 1) {
        cdc_buffer[line_length++] = c;
        return false;
    }

    else if (c == '\n') {
        cdc_buffer[line_length] = '\0';

        for (int i = 0; i <= line_length; i++) {

            if (i <= max_len - 1) {
                out[i] = cdc_buffer[i];
            }
            else {
                *error = 2;
                line_length = 0;
                out[0] = '\0';
                return true;
            }
        }
        
        line_length = 0;
        return true;
    }

    else if (line_length > sizeof(cdc_buffer) - 1) {
        *error = 1;
        line_length = 0;
        out[0] = '\0';
        return true;
    }

    return false;
}