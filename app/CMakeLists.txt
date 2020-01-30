cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

add_library (app STATIC)

target_include_directories(app
    PRIVATE
    include
    )

target_sources(app
    PRIVATE
        src/components/retained/AnalogGauge.cpp
        src/components/retained/Button.cpp
        src/components/retained/ChannelText.cpp
        src/components/retained/Slider.cpp
        src/components/retained/StackPanel.cpp
        src/components/retained/TextBlock.cpp
        src/components/retained/TextInput.cpp
        src/components/retained/Window.cpp

        src/components/immediate/RoundGauge.cpp

        src/nav/WindowManager.cpp

        src/Dispatcher.cpp

src/test.cpp)

# Group by folder tree when generating a project for an IDE
get_target_property(APP_STATIC_SOURCES app SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${APP_STATIC_SOURCES})

target_link_libraries(app imgui ecu)
