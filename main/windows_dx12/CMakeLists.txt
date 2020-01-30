
add_library(main_windows_dx12 STATIC)

target_sources(main_windows_dx12 PRIVATE main.cpp ../windows_common/imgui_impl_win32.cpp imgui_impl_dx12.cpp)

target_link_libraries(main_windows_dx12 app main_windows_common d3d12 dxgi)
