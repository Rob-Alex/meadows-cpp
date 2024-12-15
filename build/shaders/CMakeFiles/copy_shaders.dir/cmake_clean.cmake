file(REMOVE_RECURSE
  "compute.air"
  "compute.metallib"
  "shader.air"
  "shader.metallib"
  "CMakeFiles/copy_shaders"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/copy_shaders.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
