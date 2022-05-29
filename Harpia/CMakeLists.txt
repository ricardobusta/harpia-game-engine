#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(Harpia LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add project files and sources
file(GLOB Harpia_SRC CONFIGURE_DEPENDS "*.cpp")
add_library(${PROJECT_NAME} STATIC ${Harpia_SRC})

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ./ThirdParty/SDL2/include
        ./
)

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        mingw32
        SDL2main
        SDL2
        Harpia.Engine
)

add_subdirectory(Engine)
add_subdirectory(ThirdParty/SDL2)