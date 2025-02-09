#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>
#include <AppKit/AppKit.hpp> 
#include <QuartzCore/CAMetalLayer.hpp>

NS::Window* ToNSWindow(GLFWwindow* pGlfwWindow, CA::MetalLayer* pLayer); 
