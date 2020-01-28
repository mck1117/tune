cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project (imgui_tuner VERSION 1.0)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(app)
add_subdirectory(main)
add_subdirectory(lib/ecu)
add_subdirectory(lib/imgui)

add_executable(exe)
target_sources(exe PRIVATE dummy.cpp)
target_link_libraries(exe main app)
