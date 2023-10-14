cmake_minimum_required(VERSION 3.10)
project(sdl-astar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
set(SOURCE_FILES main.cpp world.cpp)

add_executable(sdl-astar ${SOURCE_FILES})

target_compile_options(sdl-astar PRIVATE -Wall -Werror)
target_compile_features(sdl-astar PRIVATE cxx_std_20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(sdl-astar ${SDL2_LIBRARIES})

