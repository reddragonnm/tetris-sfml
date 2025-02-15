cmake_minimum_required(VERSION 3.15...3.31)
project(tetris-sfml DESCRIPTION "Tetris game with SFML library" LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Collect all files recursively under src/
file(GLOB_RECURSE SRC_FILES src/*)

# Set executable name
set(EXECUTABLE_NAME "Tetris")

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_23)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SFML::Graphics)
