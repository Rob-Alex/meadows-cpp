# Create the shaders folder in the build directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

# Define file paths for compute.metal
set(COMPUTE_AIR_FILE ${CMAKE_BINARY_DIR}/shaders/compute.air)
set(COMPUTE_METALLIB_FILE ${CMAKE_BINARY_DIR}/shaders/compute.metallib)

# Compile compute.metal to AIR
add_custom_command(
    OUTPUT ${COMPUTE_AIR_FILE}
    COMMAND xcrun -sdk macosx metal -c ${CMAKE_SOURCE_DIR}/shaders/compute.metal -o ${COMPUTE_AIR_FILE}
    DEPENDS ${CMAKE_SOURCE_DIR}/shaders/compute.metal
    COMMENT "Compiling compute.metal to AIR"
)

# Compile AIR to compute.metallib
add_custom_command(
    OUTPUT ${COMPUTE_METALLIB_FILE}
    COMMAND xcrun -sdk macosx metallib ${COMPUTE_AIR_FILE} -o ${COMPUTE_METALLIB_FILE}
    DEPENDS ${COMPUTE_AIR_FILE}
    COMMENT "Compiling compute AIR to Metal library"
)

# Define file paths for shader.metal
set(SHADER_AIR_FILE ${CMAKE_BINARY_DIR}/shaders/shader.air)
set(SHADER_METALLIB_FILE ${CMAKE_BINARY_DIR}/shaders/shader.metallib)

# Compile shader.metal to AIR
add_custom_command(
    OUTPUT ${SHADER_AIR_FILE}
    COMMAND xcrun -sdk macosx metal -c ${CMAKE_SOURCE_DIR}/shaders/shader.metal -o ${SHADER_AIR_FILE}
    DEPENDS ${CMAKE_SOURCE_DIR}/shaders/shader.metal
    COMMENT "Compiling shader.metal to AIR"
)

# Compile AIR to shader.metallib
add_custom_command(
    OUTPUT ${SHADER_METALLIB_FILE}
    COMMAND xcrun -sdk macosx metallib ${SHADER_AIR_FILE} -o ${SHADER_METALLIB_FILE}
    DEPENDS ${SHADER_AIR_FILE}
    COMMENT "Compiling shader AIR to Metal library"
)

# Add a custom target to compile both shaders
add_custom_target(CompileShaders ALL
    DEPENDS ${COMPUTE_METALLIB_FILE} ${SHADER_METALLIB_FILE}
)

# Optionally, copy the compiled metallib files to a specific location
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${COMPUTE_METALLIB_FILE} ${CMAKE_BINARY_DIR}/shaders/compute.metallib
    COMMAND ${CMAKE_COMMAND} -E copy ${SHADER_METALLIB_FILE} ${CMAKE_BINARY_DIR}/shaders/shader.metallib
    DEPENDS CompileShaders
)

# Clean up generated AIR and METALLIB files during "make clean"
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "${COMPUTE_AIR_FILE};${COMPUTE_METALLIB_FILE};${SHADER_AIR_FILE};${SHADER_METALLIB_FILE}"
)
