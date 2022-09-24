add_executable(main_app main.cpp)

target_include_directories(main_app
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        )

target_link_libraries(main_app
        PRIVATE
        mbed-os
        mbed-events
        ui
        lvgl::lvgl
        lvglDriver
        ds1820
        la-t8
        mg996-r
        hx711
        )

mbed_set_post_build(main_app)

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
