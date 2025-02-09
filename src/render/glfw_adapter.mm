#import "glfw_adapter.h"

NS::Window* ToNSWindow(GLFWwindow* pGlfwWindow, CA::MetalLayer* pLayer)
{
    CALayer* pObjLayer = (__bridge CALayer*) pLayer;
    NSWindow* pObjWindow = glfwGetCocoaWindow(pGlfwWindow);

    pObjWindow.contentView.layer = pObjLayer;
    pObjWindow.contentView.wantsLayer = YES;

    return (__bridge NS::Window*)pObjWindow;
}
