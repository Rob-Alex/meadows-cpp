# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.28)

# Project details
project(meadows LANGUAGES CXX OBJCXX)

# Gather source files
file(GLOB SRC_FILES "*.cpp" "*.mm")

# Add the main executable
add_executable(meadows ${SRC_FILES})

# Include directories
target_include_directories(meadows 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_SOURCE_DIR}/lib
)

# Set Objective-C++ compile flags
target_compile_options(meadows PRIVATE -x objective-c++)

# Link the executable with required frameworks and libraries
target_link_libraries(meadows 
    PRIVATE METAL_CPP
    PRIVATE "-framework Cocoa"
    PRIVATE "-framework QuartzCore"
    PRIVATE "-framework Metal"
    PRIVATE "-framework MetalKit"
    PRIVATE glfw
)

# Find and link GLFW
find_package(glfw3 REQUIRED PATHS /opt/homebrew/Cellar/glfw/3.4.0/lib/cmake/glfw3)

# Set additional properties
set_property(TARGET meadows PROPERTY CXX_STANDARD 17)
set_property(TARGET meadows PROPERTY CXX_STANDARD_REQUIRED ON)

# Optionally print gathered source files for debugging
message(STATUS "Source files: ${SRC_FILES}")

