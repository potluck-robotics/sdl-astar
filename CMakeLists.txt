cmake_minimum_required(VERSION 3.25)
cmake_policy(SET CMP0135 NEW)
project(sdl-astar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SDL2_VERSION 2.28.2)
set(SOURCE_FILES src/main.cpp src/cursor.cpp src/world.cpp src/a_star.cpp)

include(FetchContent)
FetchContent_Declare(
    SDL2
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.28.2.tar.gz
    FIND_PACKAGE_ARGS ${SDL2_VERSION} EXACT
)
FetchContent_MakeAvailable(SDL2)

find_package(SDL2 ${SDL2_VERSION} EXACT REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static SDL2::SDL2main)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
