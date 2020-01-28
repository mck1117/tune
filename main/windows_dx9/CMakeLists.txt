
add_library(main_windows_dx9 STATIC)

target_sources(main_windows_dx9 PRIVATE main.cpp ../windows_common/imgui_impl_win32.cpp imgui_impl_dx9.cpp)

target_link_libraries(main_windows_dx9 main_windows_common d3d9)
