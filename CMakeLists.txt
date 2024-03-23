cmake_minimum_required(VERSION 3.10)
project(sdl-astar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCE_FILES src/main.cpp src/cursor.cpp src/world.cpp src/a_star.cpp)

include_directories(include)

add_executable(sdl-astar ${SOURCE_FILES})

target_compile_options(sdl-astar PRIVATE -Wall)
target_compile_features(sdl-astar PRIVATE cxx_std_20)

IF (WIN32)
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.30.1/cmake")
ENDIF()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(sdl-astar ${SDL2_LIBRARIES})

