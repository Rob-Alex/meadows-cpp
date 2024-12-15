# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.28.3)

# Add the main executable
file(GLOB SRC_FILES "*.cpp")
add_executable(meadows ${SRC_FILES})

# Link the executable with the libraries
target_link_libraries(meadows METAL_CPP)

# Include directories
target_include_directories(meadows PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(meadows PRIVATE ${CMAKE_SOURCE_DIR}/lib)
