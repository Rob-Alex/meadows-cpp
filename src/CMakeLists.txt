# Do NOT call project(...) here again
# Just add the relevant subdirectories that define libraries

add_subdirectory(compute)
add_subdirectory(render)
add_subdirectory(core)
add_subdirectory(solvers)
add_subdirectory(visualization)

message(STATUS "src/CMakeLists.txt configured.")
