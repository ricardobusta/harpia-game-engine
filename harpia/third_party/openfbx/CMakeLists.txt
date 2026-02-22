project(ThirdParty.OpenFBX CXX C)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")
set(
        ${PROJECT_NAME}_SRC
        miniz/miniz.cpp
        openfbx/src/ofbx.cpp
        openfbx/src/libdeflate.c
)
set(
        ${PROJECT_NAME}_HEADERS
        miniz/miniz.h
        openfbx/src/ofbx.h
        openfbx/src/libdeflate.h
)
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/)
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

# Suppress all warnings from this third-party library — we cannot modify its source
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:Clang,AppleClang>:-Wno-everything>
        $<$<CXX_COMPILER_ID:GNU>:-w>
        $<$<BOOL:${EMSCRIPTEN}>:-Wno-everything>
)