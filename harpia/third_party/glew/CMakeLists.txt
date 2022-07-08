cmake_minimum_required(VERSION 3.22)
project(ThirdParty.Glew)

message("++ Configure ${PROJECT_NAME}")

if (BUILD_SHARED_LIBS)
    set(GLEW_LINK glew)
else ()
    set(GLEW_LINK glew_s)
endif ()

add_library(${PROJECT_NAME} STATIC thirdparty_glew.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC glew)
target_include_directories(${PROJECT_NAME} PUBLIC glew/include)

add_subdirectory(glew/build/cmake)

#set(GLEW_CMAKE_PATH  ${CMAKE_SOURCE_DIR}/harpia/third_party/glew/glew)
#set(GLEW_CMAKE_AUTO_PATH  ${CMAKE_SOURCE_DIR}/harpia/third_party/glew/glew/auto)

#execute_process(
#        COMMAND make clean
#        WORKING_DIRECTORY ${GLEW_CMAKE_AUTO_PATH}
#        RESULT_VARIABLE ret
#)
#
#execute_process(
#        COMMAND make clean
#        WORKING_DIRECTORY ${GLEW_CMAKE_PATH}
#        RESULT_VARIABLE ret
#)
#
#execute_process(
#        COMMAND make
#        WORKING_DIRECTORY ${GLEW_CMAKE_AUTO_PATH}
#        RESULT_VARIABLE ret
#)
#
#execute_process(
#        COMMAND make
#        WORKING_DIRECTORY ${GLEW_CMAKE_PATH}
#        RESULT_VARIABLE ret
#)
#
#execute_process(
#        COMMAND make install
#        WORKING_DIRECTORY ${GLEW_CMAKE_PATH}
#        RESULT_VARIABLE ret
#)
#
#execute_process(
#        COMMAND make install.all
#        WORKING_DIRECTORY ${GLEW_CMAKE_PATH}
#        RESULT_VARIABLE ret
#)

#message("## Glew process finished: ${ret}")