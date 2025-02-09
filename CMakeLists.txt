cmake_minimum_required(VERSION 3.28)
project(meadows LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# [Optional] Auto-set CMAKE_PREFIX_PATH so 'find_package(glfw3)' can locate brew config
if(APPLE AND NOT DEFINED CMAKE_PREFIX_PATH)
    if(EXISTS "/opt/homebrew")
        set(CMAKE_PREFIX_PATH "/opt/homebrew" CACHE PATH "Prefix path for Apple Silicon Homebrew" FORCE)
        message(STATUS "Defaulting CMAKE_PREFIX_PATH to /opt/homebrew")
    elseif(EXISTS "/usr/local")
        set(CMAKE_PREFIX_PATH "/usr/local" CACHE PATH "Prefix path for Intel macOS Homebrew" FORCE)
        message(STATUS "Defaulting CMAKE_PREFIX_PATH to /usr/local")
    endif()
endif()

#
# ----> CRITICAL FIX: ensure the linker knows where to find libglfw.* <----
#
# If your brew config doesn't set an absolute path for the glfw imported target,
# the final link line sees "-lglfw" but does not see "-L/opt/homebrew/lib".
# So we manually add it:
link_directories("/opt/homebrew/lib")

# or if you want to handle intel mac as well:
# if(EXISTS "/opt/homebrew/lib")
#     link_directories("/opt/homebrew/lib")
# elseif(EXISTS "/usr/local/lib")
#     link_directories("/usr/local/lib")
# endif()

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(shaders)

add_executable(meadows src/main.cpp)

target_link_libraries(meadows
    PRIVATE compute
    PRIVATE render
    PRIVATE core
    PRIVATE solvers
    PRIVATE glfw        # <--- linking the 'glfw' target (imported target name)
    PRIVATE METAL_CPP
)

if(APPLE)
    target_link_libraries(meadows PRIVATE
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework MetalKit"
        "-framework AppKit"
    )
endif()

message(STATUS "Root CMakeLists configured.")

