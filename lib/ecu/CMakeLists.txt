add_library(ecu STATIC)

target_include_directories(ecu PUBLIC include)

target_sources(ecu
    PRIVATE
        src/Ecu.cpp
        src/OutputChannelParser.cpp
        src/OutputChannel.h
        src/OutputChannel.cpp
    )
