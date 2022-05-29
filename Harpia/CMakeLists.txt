#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(Harpia LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        Core.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/SDL2/include
        )

target_link_libraries(${PROJECT_NAME}
        SDL2-static
        Harpia.Engine
        )

add_subdirectory(Engine)
add_subdirectory(Configuration)
add_subdirectory(ThirdParty/SDL2)