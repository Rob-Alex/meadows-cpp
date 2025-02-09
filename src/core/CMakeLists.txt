cmake_minimum_required(VERSION 3.28)

add_library(core STATIC
    simulation.cpp
    simulator.cpp
    app.cpp
)


target_include_directories(core PUBLIC
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/render

)

if(TARGET glfw)
    target_link_libraries(core PUBLIC glfw)
endif()
# Link to glfw (for <GLFW/glfw3.h>) and compute (for mtl_computer.hpp)
target_link_libraries(core
    PUBLIC METAL_CPP
    PUBLIC compute
    PUBLIC render
)

if(APPLE)
    target_link_libraries(core PRIVATE
        "-framework Foundation"
        "-framework Metal"
        "-framework MetalKit"
        "-framework AppKit"
    )
endif()

message(STATUS "Core module configured.")
