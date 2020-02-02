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

        src/pal/windows/WindowsSerialPort.cpp

        src/Span.h
    )
