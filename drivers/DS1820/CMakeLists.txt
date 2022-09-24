add_library(ds1820 INTERFACE)
target_include_directories(
        ds1820
        INTERFACE
        .
        ../../include/
)

target_sources(
        ds1820
        INTERFACE
        ../libs/LinkedList.cpp
        DS1820.cpp
)