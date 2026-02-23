#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#
cmake_minimum_required(VERSION 4.1.2)
project(HarpiaGameEngine)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif ()

add_subdirectory(sample_game)
add_subdirectory(harpia)