project(Harpia.Application CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")
file(GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.h)
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/)
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_FOUND:= ${OPENGL_FOUND}")

if(OPENGL_FOUND)
    message('OPENGL_FOUND-is-true')
else()
    message('OPENGL_FOUND-is-false')
endif()
target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        Harpia.Game
        Harpia.Application.Internal
        OpenGL::GL
)
add_subdirectory(internal)