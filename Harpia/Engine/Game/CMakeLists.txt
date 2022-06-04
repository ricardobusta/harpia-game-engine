project(Harpia.Game CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/**/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/**/*.h)
include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
message("${PROJECT_NAME} source files: ${${PROJECT_NAME}_SRC}")
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/
)
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        Harpia.Application
        Harpia.Structures
)