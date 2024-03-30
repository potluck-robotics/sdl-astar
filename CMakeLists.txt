cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0135 NEW)
project(sdl-astar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCE_FILES src/main.cpp src/cursor.cpp src/world.cpp src/a_star.cpp)

include_directories(include)

add_executable(sdl-astar ${SOURCE_FILES})

target_compile_options(sdl-astar PRIVATE -Wall)
target_compile_features(sdl-astar PRIVATE cxx_std_20)

include(FetchContent)

FetchContent_Declare(
    SDL2
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.0.20.tar.gz
)

FetchContent_GetProperties(SDL2)
if(NOT SDL2_POPULATED)
    FetchContent_Populate(SDL2)
    add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
endif()

include_directories(${sdl2_SOURCE_DIR}/include)
target_link_libraries(sdl-astar SDL2::SDL2)