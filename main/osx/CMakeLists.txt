
add_library(main_osx STATIC)

target_sources(main_osx PRIVATE
    main.mm
    imgui_impl_osx.mm
    )

target_link_libraries(main_osx app imgui_opengl)

target_link_libraries(main_osx "-framework Cocoa")
