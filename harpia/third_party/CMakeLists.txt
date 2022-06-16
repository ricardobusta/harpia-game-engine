if (NOT EMSCRIPTEN)
    add_subdirectory(gl3w)      # Desktop-only OpenGL loader
    add_subdirectory(googletest) # Desktop-only unit test framework
endif ()

add_subdirectory(glm)
add_subdirectory(openfbx)
add_subdirectory(sdl)
add_subdirectory(sdl_image)
add_subdirectory(sdl_mixer)
add_subdirectory(sdl_ttf)
add_subdirectory(imgui)