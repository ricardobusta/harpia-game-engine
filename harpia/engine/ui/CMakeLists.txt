project(Harpia.Ui CXX)
set(CMAKE_CXX_STANDARD 17)

message("++ Configure ${PROJECT_NAME}")

# Path to imgui source and its backends
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/../../third_party/imgui/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)

file(GLOB ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/hge/*.h)

add_library(${PROJECT_NAME} STATIC
        ${${PROJECT_NAME}_SRC}
        ${IMGUI_BACKENDS_DIR}/imgui_impl_sdl3.cpp
        ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
)
target_sources(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

target_include_directories(${PROJECT_NAME}
        PUBLIC  ${PROJECT_SOURCE_DIR}/
        PRIVATE ${IMGUI_BACKENDS_DIR}  # for bare "imgui_impl_*.h" includes inside backend .cpp files
)

# On Emscripten the OpenGL ES 3 headers ship with the SDK; tell the ImGui
# backend to use them instead of its bundled desktop loader.
if (EMSCRIPTEN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_OPENGL_ES3)
endif ()

target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        Harpia.Core
        Harpia.Rendering
        ImGui
        SDL3::SDL3
)
