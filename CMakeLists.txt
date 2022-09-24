cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")

include(${MBED_PATH}/tools/cmake/app.cmake)

project(fyp18-03
        VERSION 1.0
        DESCRIPTION "Final year project firmware"
        LANGUAGES C CXX
        )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

set(LV_CONF_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h
        CACHE STRING "" FORCE)

add_subdirectory(${MBED_PATH})
add_subdirectory(custom_targets)
add_subdirectory(lvgl)
add_subdirectory(lvglDriver)
target_include_directories(lvglDriver INTERFACE lvgl)
add_subdirectory(drivers)
add_subdirectory(apps)
add_subdirectory(ui)


