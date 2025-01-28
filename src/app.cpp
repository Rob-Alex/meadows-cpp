#include "app.hpp"
#include "glfw_adapter.h"

App::App()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    _pGLFWwindow = glfwCreateWindow(1000, 1000, "Meadows", NULL, NULL);
    glfwSetWindowUserPointer(_pGLFWwindow, this);

    // Set GLFW mouse input callbacks
    glfwSetCursorPosCallback(_pGLFWwindow, App::mouseMoveCallback);
    glfwSetMouseButtonCallback(_pGLFWwindow, App::mouseButtonCallback);

    _pDevice = MTL::CreateSystemDefaultDevice();

    _pMTLlayer = CA::MetalLayer::layer()->retain();
    _pMTLlayer->setDevice(_pDevice);

    _pMTLlayer->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

    _pWindow = ToNSWindow(_pGLFWwindow, _pMTLlayer)->retain();

    _pSimulator = new TestSimulator(_pDevice, 100, 100);

    _pSimulator->initialize();

    _pRenderer = new Renderer(_pDevice, _pSimulator, _pMTLlayer);
}


App::~App() {
    _pWindow->release();
    delete _pRenderer;
    delete _pSimulator;
    glfwTerminate();
}

void App::run() {

    while (!glfwWindowShouldClose(_pGLFWwindow)) { 
        glfwPollEvents();
        //static auto lastFPSUpdateTime = std::chrono::high_resolution_clock::now();
        //static size_t frameCount = 0;
        //static double frameTimeAccumulator = 0.0;

        // Calculate time elapsed
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();  
        float timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime).count() / 1e6f;

        MTL::CommandBuffer* pSimulationCmd = _pSimulator->getCommandQueue()->commandBuffer();
        // Update simulation with cumulative time
        _pSimulator->update(timeElapsed);
        pSimulationCmd->commit();
        pSimulationCmd->waitUntilCompleted();

        // Update renderer with the latest simulation data
        MTL::CommandBuffer* pRenderCmd = _pRenderer->getCommandQueue()->commandBuffer();
        _pRenderer->updateMeshData();
        _pRenderer->updateBuffers();
    // Draw the updated frame
        _pRenderer->draw();
        pRenderCmd->commit();
        pRenderCmd->waitUntilCompleted();

    // Measure frame duration
    //auto endTime = std::chrono::high_resolution_clock::now();
    //double frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - currentTime).count() / 1e6;

    // Accumulate frame time and increment frame count
    //frameTimeAccumulator += frameDuration;
    //frameCount++;
    
    //auto elapsedSinceLastUpdate = std::chrono::duration_cast<std::chrono::seconds>(endTime - lastFPSUpdateTime).count();

    /*
    if (elapsedSinceLastUpdate >= 1) {
        // Calculate average FPS
        double averageFPS = frameCount / frameTimeAccumulator;

        // Clear the terminal line and print FPS
        printf("\033[2K\rAverage FPS: %.2f", averageFPS);
        fflush(stdout); // Force the output to be written immediately

        // Reset for the next interval
        frameCount = 0;
        frameTimeAccumulator = 0.0;
        lastFPSUpdateTime = endTime;
    }*/
    

    }
} 

// Mouse movement callback
void App::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    __builtin_printf("Mouse moved to: (%f, %f). \n ", xpos, ypos);
}

// Mouse button callback
void App::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        // Retrieve the App instance
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (!app || !app->_pSimulator) {
            __builtin_printf("Error: App instance or simulator is null.\n");
            return;
        }

        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        __builtin_printf("Mouse button %d pressed at (%f, %f).\n", button, xpos, ypos);
    }
}

