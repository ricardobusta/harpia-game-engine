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

target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        gl3w
        Harpia.Core
        Harpia.Application.Internal
        Harpia.Game.Internal
        SDL2_image
)