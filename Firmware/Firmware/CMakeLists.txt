cmake_minimum_required(VERSION 3.13)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(red_ducky_0.3 C CXX ASM)

pico_sdk_init()

add_executable(red_ducky_0.3 
    main.c
    layout.c
    parser.c
    usb_descriptors.c
)

target_include_directories(red_ducky_0.3 PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(red_ducky_0.3    
    pico_stdlib 
    tinyusb_device 
    tinyusb_board
)

pico_add_extra_outputs(red_ducky_0.3)
