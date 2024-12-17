#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/robbiealexander/Projects/Cpp/meadows/shaders
  xcrun -sdk macosx metal -c /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.metal -o /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.air
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/robbiealexander/Projects/Cpp/meadows/shaders
  xcrun -sdk macosx metal -c /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.metal -o /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.air
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/robbiealexander/Projects/Cpp/meadows/shaders
  xcrun -sdk macosx metal -c /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.metal -o /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.air
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/robbiealexander/Projects/Cpp/meadows/shaders
  xcrun -sdk macosx metal -c /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.metal -o /Users/robbiealexander/Projects/Cpp/meadows/shaders/shader.air
fi

