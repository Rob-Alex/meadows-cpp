cmake_minimum_required(VERSION 3.28)

add_library(METAL_CPP INTERFACE)

# This ensures you can #include <Foundation/Foundation.hpp> & <Metal/Metal.hpp>
target_include_directories(METAL_CPP INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/metal-cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/metal-cpp-extensions"
)

message(STATUS "Metal-CPP configured at: ${CMAKE_CURRENT_SOURCE_DIR}")
