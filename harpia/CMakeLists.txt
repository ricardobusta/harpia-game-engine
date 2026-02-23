#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#
cmake_minimum_required(VERSION 4.1.2)
project(Harpia CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
if (EMSCRIPTEN)
    message("== EMSCRIPTEN Build")
    option(BUILD_SHARED_LIBS "" OFF)
    set(SDL3MIXER_VENDORED OFF)
    set(SDL3MIXER_MOD OFF)
    # Disable SDL3_image backends that require native libs not in Emscripten sysroot
    set(SDL3IMAGE_AVIF OFF)
    set(SDL3IMAGE_WEBP OFF)
    # Do not propagate -Werror to Emscripten builds — third-party code produces
    # extra warnings under Emscripten's stricter frontend that are not actionable.
else ()
    message("== Desktop Build")
    option(BUILD_SHARED_LIBS "" ON)
    set(SDL3MIXER_VENDORED ON)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # Treat warnings as errors (MSVC)
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror") # Treat warnings as errors (GCC/Clang)
    endif ()
endif ()

set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)
set(SDL3MIXER_FLAC OFF)
set(SDL3MIXER_OPUS OFF)
set(SDL3MIXER_OGG ON)

list(
        APPEND
        ${PROJECT_NAME}_INCLUDES
        third_party/glm/
        third_party/sdl/include/
        third_party/sdl_mixer/include/
        third_party/sdl_image/include/
        third_party/sdl_ttf/include/
)

include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES})

if (BUILD_SHARED_LIBS)
    message("== Building Harpia Shared")
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SRC})
else()
    message("== Building Harpia Static")
    add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
endif()

# TODO In order to generate webgl builds, need to also create a static lib with static dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC Harpia.Application)

target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES})

add_subdirectory(engine)
add_subdirectory(third_party)

# With Mingw64 compiler, these DLL are required to run the app on Windows.
# Guard with EXISTS so MSVC builds (which don't have these files) are not broken.
IF (WIN32)
    get_filename_component(COMPILER_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)
    foreach (_dll libwinpthread-1.dll libstdc++-6.dll libgcc_s_seh-1.dll)
        if (EXISTS "${COMPILER_PATH}/${_dll}")
            file(COPY "${COMPILER_PATH}/${_dll}" DESTINATION "${CMAKE_BINARY_DIR}/bin/")
        endif ()
    endforeach ()
endif (WIN32)

if (NOT EMSCRIPTEN)
    enable_testing()
    file(GLOB_RECURSE ${PROJECT_NAME}_TESTS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/**/*.tests.cpp)
    message(${PROJECT_NAME}_TESTS - ${${PROJECT_NAME}_TESTS})
    add_executable(
            ${PROJECT_NAME}.Tests
            ${${PROJECT_NAME}_TESTS}
    )
    target_link_libraries(
            ${PROJECT_NAME}.Tests
            gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}.Tests)
endif ()