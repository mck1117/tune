add_library(imgui_opengl STATIC)
target_include_directories(imgui_opengl PUBLIC .)
target_sources(imgui_opengl PRIVATE imgui_impl_opengl2.cpp)
target_link_libraries(imgui_opengl imgui)

if (APPLE)
    target_link_libraries(imgui_opengl "-framework OpenGL")
else ()
    find_package(OpenGL REQUIRED)

    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)

    target_include_directories(imgui_opengl PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
    target_link_libraries(imgui_opengl pthread ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})
endif()
