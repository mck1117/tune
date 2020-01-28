
add_library(main_windows STATIC)

target_sources(main_windows PRIVATE main.cpp imgui_impl_win32.cpp)

target_link_libraries(main_windows imgui_dx9 d3d9)
