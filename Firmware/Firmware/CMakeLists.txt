cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(rubber_ducky_fw C CXX ASM)

pico_sdk_init()

add_executable(rubber_ducky_fw
    main.c
    usb_descriptors.c
)
target_include_directories(rubber_ducky_fw PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(rubber_ducky_fw
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(rubber_ducky_fw)
