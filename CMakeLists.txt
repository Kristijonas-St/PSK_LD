cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(PSK_LD VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect all source files
file(GLOB_RECURSE SOURCES
    application/*.cpp
)

# Create the executable
add_executable(psk_ld ${SOURCES})

# Include directories for headers
target_include_directories(psk_ld PRIVATE
    ${PROJECT_SOURCE_DIR}/application
    ${PROJECT_SOURCE_DIR}/application/players
    ${PROJECT_SOURCE_DIR}/application/players/computer
    ${PROJECT_SOURCE_DIR}/application/players/user
    ${PROJECT_SOURCE_DIR}/application/ui
    ${PROJECT_SOURCE_DIR}/application/game
)
