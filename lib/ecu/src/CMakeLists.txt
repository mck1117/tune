add_library(ecu STATIC)

target_include_directories(ecu
    PRIVATE
        .
    PUBLIC
        ../include
    )

target_sources(ecu
    PRIVATE
        Ecu.h
        Ecu.cpp
        EcuInit.cpp
        FakeEcu.h
        FakeEcu.cpp

        channels/OutputChannel.h
        channels/OutputChannelParser.h
        channels/OutputChannelParser.cpp
        channels/FakeOutputChannel.h
        channels/FakeOutputChannel.cpp

        interface/EcuInterface.h
        interface/TunerstudioProtocol.h
        interface/TunerstudioProtocol.cpp
        interface/TunerstudioTransport.cpp

        Span.h
    )

# PAL components
if (WIN32)
    target_sources(ecu PRIVATE pal/windows/WindowsSerialPort.cpp)
elseif (APPLE)
    target_sources(ecu PRIVATE pal/mac/MacSerialPort.cpp)
else()
    target_sources(ecu PRIVATE pal/linux/LinuxSerialPort.cpp)
endif()

# Group by folder tree when generating a project for an IDE
get_target_property(ECU_STATIC_SOURCES ecu SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${ECU_STATIC_SOURCES})
