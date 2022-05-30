#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(Harpia)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(
        ${PROJECT_NAME} PUBLIC
        ThirdParty/SDL/include
        ThirdParty/glew-2.2.0/include
)

add_library(${PROJECT_NAME} STATIC ${Harpia_SRC})

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        mingw32
        SDL2main
        SDL2
        glew
        SDL2_image
        SDL2_ttf
        Harpia.Engine.Application
        Harpia.Engine.Structures
)

target_sources(${PROJECT_NAME} PUBLIC ${Harpia_SRC} ${Harpia_HEADERS})

add_subdirectory(ThirdParty/SDL)
add_subdirectory(ThirdParty/SDL_image)
add_subdirectory(ThirdParty/SDL_mixer)
#add_subdirectory(ThirdParty/SDL_ttf)
add_subdirectory(ThirdParty/glew-2.2.0/build/cmake)
add_subdirectory(Engine/Application)
add_subdirectory(Engine/Structures)
add_subdirectory(Engine/Core)