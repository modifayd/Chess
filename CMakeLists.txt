cmake_minimum_required(VERSION 3.10)   # Require CMake version
project(MyProject)                     # Project name

set(CMAKE_CXX_STANDARD 17)             # Use C++17

# Include header directory
include_directories(include)

# Define executable with sources
add_executable(chess
    main.cpp
    src/chess.cpp
)
