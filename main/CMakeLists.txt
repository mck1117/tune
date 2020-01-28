add_library(main STATIC)

target_sources(main PRIVATE dummy.cpp)

if (WIN32)
    add_subdirectory(dx9)
    add_subdirectory(windows)
    target_link_libraries(main main_windows)
elseif (APPLE)
    add_subdirectory(osx)
    add_subdirectory(opengl)
    target_link_libraries(main main_osx)
endif()
