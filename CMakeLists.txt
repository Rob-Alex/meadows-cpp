cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 17)
project(meadows)

add_subdirectory(src)  # Add target
add_subdirectory(metal-cmake)  # Library definition
add_subdirectory(shaders)

add_dependencies(${PROJECT_NAME} CompileShaders)

