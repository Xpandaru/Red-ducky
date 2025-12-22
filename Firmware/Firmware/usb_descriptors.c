#include "tusb.h"

uint8_t const desc_hid_report[] =
{
    TUD_HID_REPORT_DESC_KEYBOARD()
};

uint8_t const *tud_hid_descriptor_report_cb(void)
{
    return desc_hid_report;
}

uint16_t tud_hid_descriptor_report_size_cb(void)
{
    return sizeof(desc_hid_report);
}
