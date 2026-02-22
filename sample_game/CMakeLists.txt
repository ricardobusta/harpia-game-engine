#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(Harpia.SampleGame LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_SUB CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/scenes/*.cpp
        ${PROJECT_SOURCE_DIR}/scripts/*.cpp)
list(APPEND ${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC_SUB})

file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS_SUB CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/scenes/*.h
        ${PROJECT_SOURCE_DIR}/scripts/*.h)
list(APPEND ${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS_SUB})
include_directories(
        scenes
        scripts
)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

set(HARPIA_APPLICATION_TYPE "")

if (CMAKE_BUILD_TYPE MATCHES Debug)
else ()
    if (WIN32)
        set(HARPIA_APPLICATION_TYPE WIN32)
    endif ()
endif ()

add_executable(${PROJECT_NAME} ${HARPIA_APPLICATION_TYPE} ${${PROJECT_NAME}_SRC} ${APP_ICON_RESOURCE_WINDOWS})
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC Harpia)

#install_symlink(${CMAKE_CURRENT_SOURCE_DIR}/Assets/ ${CMAKE_BINARY_DIR}/bin/Assets/)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ DESTINATION ${CMAKE_BINARY_DIR}/bin/Assets/)

if (EMSCRIPTEN)
    target_link_options(${PROJECT_NAME} PRIVATE
            "SHELL:-s ALLOW_MEMORY_GROWTH=1"
            "SHELL:-s INITIAL_MEMORY=64MB"
            "SHELL:-s STACK_SIZE=8MB"
            "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets@/assets"
    )
    # Use custom HTML shell if available
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../build_scripts/emscripten_shell.html")
        target_link_options(${PROJECT_NAME} PRIVATE
                "--shell-file" "${CMAKE_CURRENT_SOURCE_DIR}/../build_scripts/emscripten_shell.html"
        )
    endif ()
endif ()