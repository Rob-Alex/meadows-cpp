cmake_minimum_required(VERSION 3.28)

# No project(...) here unless you specifically want 'external' to be a separate project
# Typically, we just add the subdirectories for external libraries

add_subdirectory(GLFW)
add_subdirectory(metal-cmake)

# If you have other external dependencies, add_subdirectory(...) them here

message(STATUS "External dependencies configured: GLFW, Metal-CPP.")
