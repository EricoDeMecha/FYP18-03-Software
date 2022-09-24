add_library(hx711 INTERFACE)
target_include_directories(
        hx711
        INTERFACE
        .
        ../../include/
)

target_sources(
        hx711
        INTERFACE
        ../libs/LinkedList.cpp
        Hx711.cpp
)