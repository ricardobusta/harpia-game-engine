project(Harpia.Rendering CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")
file(
        GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/hge/*.cpp
        ${PROJECT_SOURCE_DIR}/hge/system_gl/*.cpp
)

file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.h)
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/)
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

if (BUILD_SHARED_LIBS)
    set(SDL_IMAGE_LINK SDL3_image-shared)
else ()
    set(SDL_IMAGE_LINK SDL3_image-static)
endif ()

if (NOT EMSCRIPTEN)
    set(GL3W_LINK gl3w)
else ()
    set(GL3W_LINK "")
endif ()

target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        ${GL3W_LINK}
        Harpia.Core
        Harpia.Application.Internal
        Harpia.Game.Internal
        ${SDL_IMAGE_LINK}
)