cmake_minimum_required(VERSION 3.28)

add_library(compute STATIC
    cpu_computer.cpp
    mtl_computer.cpp
)

# So that "mtl_computer.hpp" is visible when linking to 'compute':
target_include_directories(compute PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/compute
)

# If you use Metal-CPP:
target_link_libraries(compute PRIVATE METAL_CPP)

if(APPLE)
    target_link_libraries(compute PRIVATE 
        "-framework Metal"
        "-framework MetalKit"
        "-framework Foundation"
        "-framework AppKit"
    )
endif()

message(STATUS "Compute module configured.")
