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

# ---------------------------------------------------------------------------
# Assets: symlink (Debug/RelWithDebInfo) or copy (Release) next to the binary.
# Emscripten skips this — assets are baked in via --preload-file below.
# ---------------------------------------------------------------------------
if (NOT EMSCRIPTEN)
    set(ASSETS_SRC "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    set(ASSETS_DST "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")

    if (CMAKE_BUILD_TYPE MATCHES "Debug|RelWithDebInfo")
        # Symlink so changes to source assets are visible immediately without rebuild.
        # cmake -E rm -rf removes a symlink without following it on Unix/Windows.
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rm -rf "${ASSETS_DST}"
            COMMAND ${CMAKE_COMMAND} -E create_symlink "${ASSETS_SRC}" "${ASSETS_DST}"
            COMMENT "Assets: symlinking ${ASSETS_SRC} -> ${ASSETS_DST}"
            VERBATIM
        )
    else()
        # Full copy so the Release output folder is self-contained.
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rm -rf "${ASSETS_DST}"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SRC}" "${ASSETS_DST}"
            COMMENT "Assets: copying ${ASSETS_SRC} -> ${ASSETS_DST}"
            VERBATIM
        )
    endif()
endif()

if (EMSCRIPTEN)
    target_link_options(${PROJECT_NAME} PRIVATE
            "SHELL:-s ALLOW_MEMORY_GROWTH=1"
            "SHELL:-s INITIAL_MEMORY=64MB"
            "SHELL:-s STACK_SIZE=8MB"
            "SHELL:-s MIN_WEBGL_VERSION=2"
            "SHELL:-s MAX_WEBGL_VERSION=2"
            "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets@/assets"
    )
    # Use custom HTML shell if available
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../build_scripts/emscripten_shell.html")
        target_link_options(${PROJECT_NAME} PRIVATE
                "--shell-file" "${CMAKE_CURRENT_SOURCE_DIR}/../build_scripts/emscripten_shell.html"
        )
    endif ()
endif ()