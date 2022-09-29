# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET fyp18-03)

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})
# Force the use of LVGL configurations
set(LV_CONF_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h
        CACHE STRING "" FORCE)

add_subdirectory(${MBED_PATH})
add_subdirectory(custom_targets)

#set(MICROPY_DIR "dummy to force lvgl to use static ")
add_subdirectory(lvgl)
add_subdirectory(lvglDriver)
target_include_directories(lvglDriver INTERFACE lvgl)

set(SOURCES
        src/globals.cpp
        ui/ui_helpers.cpp
        ui/ui.cpp
        src/globals.cpp
        src/Servo.cpp
        src/LA_T8.cpp
        src/OneWire.cpp
        src/DS1820.cpp
        src/HX711.cpp
        src/AppController.cpp
        )

add_executable(${APP_TARGET}
        main.cpp
        ${SOURCES}
        )

target_link_libraries(${APP_TARGET}
        PRIVATE
        mbed-os
        mbed-events
        lvgl::lvgl
        lvglDriver
        )

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()