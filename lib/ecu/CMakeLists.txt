add_library(ecu STATIC)

target_include_directories(ecu
    PRIVATE
        src
    PUBLIC
        include
    )

target_sources(ecu
    PRIVATE
        src/Ecu.h
        src/Ecu.cpp
        src/EcuInit.cpp

        src/channels/OutputChannel.h
        src/channels/OutputChannelParser.h
        src/channels/OutputChannelParser.cpp

        src/interface/EcuInterface.h
        src/interface/TunerstudioProtocol.h
        src/interface/TunerstudioProtocol.cpp
        src/interface/TunerstudioTransport.cpp

        src/Span.h
    )

# PAL components
if (WIN32)
    target_sources(ecu PRIVATE src/pal/windows/WindowsSerialPort.cpp)
elseif (APPLE)
    target_sources(ecu PRIVATE src/pal/mac/MacSerialPort.cpp)
endif()

# Group by folder tree when generating a project for an IDE
get_target_property(ECU_STATIC_SOURCES ecu SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${ECU_STATIC_SOURCES})
