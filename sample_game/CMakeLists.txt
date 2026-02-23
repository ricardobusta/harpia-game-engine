#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 4.1.2)
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
    # Use custom HTML shell if present next to this CMakeLists.txt
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/emscripten_shell.html")
        target_link_options(${PROJECT_NAME} PRIVATE
                "--shell-file" "${CMAKE_CURRENT_SOURCE_DIR}/emscripten_shell.html"
        )
    endif ()

    # ---------------------------------------------------------------------------
    # serve target: build then immediately host on localhost for quick testing.
    # Usage: cmake --build --preset serve
    #        cmake --workflow --preset serve   (configure + build in one step)
    # ---------------------------------------------------------------------------
    set(HARPIA_WEB_PORT "8080" CACHE STRING "Port for the 'serve' target")
    set(_SERVE_URL "http://localhost:${HARPIA_WEB_PORT}/${PROJECT_NAME}.html")
    add_custom_target(serve
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "  Open: ${_SERVE_URL}"
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND python3 -m http.server ${HARPIA_WEB_PORT}
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        USES_TERMINAL
        COMMENT "Serving ${_SERVE_URL}"
        VERBATIM
    )
    add_dependencies(serve ${PROJECT_NAME})

    # ---------------------------------------------------------------------------
    # itch target: package build output into build/itch_upload.zip for itch.io.
    # Usage: cmake --build --preset itch
    #        cmake --workflow --preset itch
    # ---------------------------------------------------------------------------
    set(_ITCH_DIR "${CMAKE_SOURCE_DIR}/build/itch_upload")
    set(_ITCH_ZIP "${CMAKE_SOURCE_DIR}/build/itch_upload.zip")
    add_custom_target(itch
        COMMAND ${CMAKE_COMMAND} -E rm -rf  "${_ITCH_DIR}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_ITCH_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.html"
                "${_ITCH_DIR}/index.html"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.js"
                "${_ITCH_DIR}/"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.wasm"
                "${_ITCH_DIR}/"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.data"
                "${_ITCH_DIR}/"
        COMMAND ${CMAKE_COMMAND} -E tar "cf" "${_ITCH_ZIP}" --format=zip -- .
        WORKING_DIRECTORY "${_ITCH_DIR}"
        DEPENDS ${PROJECT_NAME}
        COMMENT "Packaging → build/itch_upload.zip"
        VERBATIM
    )
endif ()