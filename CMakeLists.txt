cmake_minimum_required(VERSION 3.24)

project(SCOOT-Engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# --------------------------------------------------
# OpenGL
# --------------------------------------------------

find_package(OpenGL REQUIRED)

# --------------------------------------------------
# SDL2
# --------------------------------------------------

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.11
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SDL2)

# --------------------------------------------------
# GLEW
# --------------------------------------------------

set(GLEW_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external/glew")

find_path(
    GLEW_INCLUDE_DIR
    NAMES GL/glew.h
    PATHS "${GLEW_ROOT}/include"
    NO_DEFAULT_PATH
    REQUIRED
)

find_library(
    GLEW_LIBRARY
    NAMES glew32
    PATHS "${GLEW_ROOT}/lib/Release/x64"
    NO_DEFAULT_PATH
    REQUIRED
)

add_library(GLEW::GLEW UNKNOWN IMPORTED GLOBAL)

set_target_properties(
    GLEW::GLEW
    PROPERTIES
        IMPORTED_LOCATION "${GLEW_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}"
)

# --------------------------------------------------
# GLM
# --------------------------------------------------

FetchContent_Declare(
    GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(GLM)

# --------------------------------------------------
# Dear ImGui
# --------------------------------------------------

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.8
    GIT_SHALLOW TRUE
)

FetchContent_GetProperties(imgui)

if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
endif()

add_library(imgui STATIC
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui PUBLIC
    "${imgui_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}/backends"
)

target_link_libraries(imgui PUBLIC
    SDL2::SDL2
    OpenGL::GL
)

# --------------------------------------------------
# Executable
# --------------------------------------------------

add_executable(SCOOT-Engine
    src/main.cpp
)

# --------------------------------------------------
# Distribution
# --------------------------------------------------

install(
    TARGETS SCOOT-Engine
    RUNTIME DESTINATION .
)

install(
    FILES "${GLEW_ROOT}/bin/Release/x64/glew32.dll"
    DESTINATION .
)

add_custom_command(TARGET SCOOT-Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        --install "${CMAKE_BINARY_DIR}"
        --prefix "${CMAKE_SOURCE_DIR}/dist"
        --config "$<CONFIG>"
)

target_include_directories(SCOOT-Engine PRIVATE
    "${sdl2_SOURCE_DIR}/include"
)

target_link_libraries(SCOOT-Engine PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    GLEW::GLEW
    OpenGL::GL
    glm::glm
    imgui
)