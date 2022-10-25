#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#
cmake_minimum_required(VERSION 3.22)
project(HarpiaGameEngine)

if (EMSCRIPTEN)
    # TODO temporary workaround until I figure out why the project does not compile with EMSCRIPTEN
    add_subdirectory(hello_world)
else ()
    add_subdirectory(sample_game)
    add_subdirectory(harpia)
endif ()
