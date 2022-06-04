#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(Harpia CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(
        APPEND
        ${PROJECT_NAME}_INCLUDES
        ThirdParty/SDL/include
        ThirdParty/glew-2.2.0/include
)

include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES})

add_library(${PROJECT_NAME} SHARED ${Harpia_SRC})

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        mingw32
        SDL2main
        SDL2
        glew
        SDL2_image
        #SDL2_ttf
        Harpia.Application
        Harpia.Game
        Harpia.Structures
)

target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES})

add_subdirectory(ThirdParty/SDL)
add_subdirectory(ThirdParty/SDL_image)
add_subdirectory(ThirdParty/SDL_mixer)
#add_subdirectory(ThirdParty/SDL_ttf)
add_subdirectory(ThirdParty/glew-2.2.0/build/cmake)
add_subdirectory(Engine/Application)
add_subdirectory(Engine/Game)
add_subdirectory(Engine/Structures)

if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/bin/glew32d.dll ${CMAKE_BINARY_DIR}/
    )
endif ()