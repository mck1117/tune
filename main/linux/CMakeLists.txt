
add_library(main_linux STATIC)

target_sources(main_linux
    PRIVATE
        main.cpp
        imgui_impl_glfw.h
        imgui_impl_glfw.cpp
    )

target_link_libraries(main_linux app imgui_opengl)
