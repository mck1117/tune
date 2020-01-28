
add_library(imgui STATIC)

target_sources(imgui
    PRIVATE
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
    )

target_include_directories(imgui
    PUBLIC
        imgui
    )
