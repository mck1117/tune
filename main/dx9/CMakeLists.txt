add_library(imgui_dx9 STATIC)
target_include_directories(imgui_dx9 PUBLIC .)
target_sources(imgui_dx9 PRIVATE imgui_impl_dx9.cpp)
target_link_libraries(imgui_dx9 imgui)
