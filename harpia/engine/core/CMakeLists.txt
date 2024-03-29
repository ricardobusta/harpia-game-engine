project(Harpia.Core CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")
file(GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.h)
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/)

if (BUILD_SHARED_LIBS)
    set(SDL_LINK SDL2)
else ()
    set(SDL_LINK SDL2-static)
endif ()
target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        mingw32
        ${SDL_LINK}
        Harpia.Debug
        Harpia.Structures
)