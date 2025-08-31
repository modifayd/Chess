cmake_minimum_required(VERSION 3.10)
project(ChessGUI)

# Require C++17
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
add_executable(ChessGUI ${SOURCES})

# Link SFML libraries
target_link_libraries(ChessGUI sfml-graphics sfml-window sfml-system)

# Optional: set output directory for binaries
set_target_properties(ChessGUI PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
