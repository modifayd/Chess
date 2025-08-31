cmake_minimum_required(VERSION 3.10)
project(chess_visual)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include your headers
include_directories(include)

# Source files
set(SOURCES
    game_gui.cpp
    src/chess.cpp
)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Create executable
add_executable(chess_visual ${SOURCES})

# Link SFML (modern CMake style)
target_link_libraries(chess_visual PRIVATE sfml-graphics sfml-window sfml-system)
