cmake_minimum_required(VERSION 3.28)

add_library(render STATIC
    renderer.cpp
    glfw_adapter.mm
)

# If you have public headers in include/render, expose them here if needed:
target_include_directories(render PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/render
)

# Link libraries that 'render' directly depends on:
# 1) 'core' if you use simulator.hpp or other core code
# 2) 'glfw' if you also include <GLFW/glfw3.h> in render code
target_link_libraries(render
    PRIVATE core
)

if(glfw3_FOUND)
    target_link_libraries(render PRIVATE glfw)
elseif(glfw_FOUND)
    target_link_libraries(render PRIVATE glfw)
endif()

if(APPLE)
    target_link_libraries(render PRIVATE
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework MetalKit"
    )
endif()

message(STATUS "Render module configured.")
