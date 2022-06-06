project(Harpia.Core CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")
file(GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/**/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/**/*.h)
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})
target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/Structures
)
target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        mingw32
        SDL2main
        SDL2
)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(
            ${PROJECT_NAME} PUBLIC
            -DHARPIA_DEBUG
            -DNDEBUG
    )
endif()