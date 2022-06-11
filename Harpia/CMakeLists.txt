#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(Harpia CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Werror) # Handle warnings as errors

option(SUPPORT_OGG "" ON)
#option(SUPPORT_MP3_MPG123 "" ON) # TODO Temporarily disabled until figure out MP3 dependencies

list(
        APPEND
        ${PROJECT_NAME}_INCLUDES
        ThirdParty/SDL/include
        ThirdParty/glew-2.2.0/include
)

include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES})

add_library(${PROJECT_NAME} SHARED ${Harpia_SRC})

# TODO In order to generate webgl builds, need to also create a static lib with static dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC Harpia.Application)

target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES})

add_subdirectory(ThirdParty/SDL)
add_subdirectory(ThirdParty/SDL_image)
add_subdirectory(ThirdParty/SDL_mixer)
add_subdirectory(ThirdParty/SDL_ttf)
add_subdirectory(ThirdParty/glew-2.2.0/build/cmake)
add_subdirectory(Engine/Application)
add_subdirectory(Engine/Audio)
add_subdirectory(Engine/Core)
add_subdirectory(Engine/Debug)
add_subdirectory(Engine/Game)
add_subdirectory(Engine/Input)
add_subdirectory(Engine/Rendering)
add_subdirectory(Engine/Structures)