add_library(la-t8 INTERFACE)
target_include_directories(
        la-t8
        INTERFACE
        .
        ../../include/
)

target_sources(
        la-t8
        INTERFACE
        LA_T8.cpp
)
