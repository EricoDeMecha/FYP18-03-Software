add_library(mg996-r INTERFACE)
target_include_directories(
        mg996-r
        INTERFACE
        .
        ../../include
)

target_sources(mg996-r
        INTERFACE
        ServoController.cpp
        )