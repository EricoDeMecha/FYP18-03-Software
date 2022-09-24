add_library(ui INTERFACE)
target_include_directories(ui
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_sources(ui
        INTERFACE
        ui.c
        ui_helpers.c
        ui_handler.c
        )