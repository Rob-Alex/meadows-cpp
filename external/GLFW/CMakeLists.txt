cmake_minimum_required(VERSION 3.28)

message(STATUS "Looking for system-installed GLFW...")

# Attempt to locate a CMake config for Brew-installed glfw
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    # Some older setups might call it 'glfw'
    find_package(glfw QUIET)
endif()

if(NOT glfw3_FOUND AND NOT glfw_FOUND)
    message(FATAL_ERROR
        "Could not find a system-installed GLFW library. "
        "On macOS, try 'brew install glfw', and re-run cmake with "
        "-DCMAKE_PREFIX_PATH=/opt/homebrew"
    )
endif()

if(glfw3_FOUND)
    message(STATUS "GLFW found via 'glfw3Config.cmake', target name is likely 'glfw'.")
elseif(glfw_FOUND)
    message(STATUS "GLFW found via 'glfw' config.")
endif()

