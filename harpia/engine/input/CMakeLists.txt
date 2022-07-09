project(Harpia.Input CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")
file(GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.h)
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/)
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})
target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        Harpia.Core
)

enable_testing()
file(GLOB ${PROJECT_NAME}_TESTS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/tests/*.cpp)
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