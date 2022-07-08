project(ThirdParty.OpenFBX CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")
set(
        ${PROJECT_NAME}_SRC
        miniz/miniz.cpp
        openfbx/src/ofbx.cpp
)
set(
        ${PROJECT_NAME}_HEADERS
        miniz/miniz.h
        openfbx/src/ofbx.h
)
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/)
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})