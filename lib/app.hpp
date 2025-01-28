#ifndef app_hpp
#define app_hpp

#include "config.hpp"
#include "renderer.hpp"
#include "simulator.hpp"

class App 
{
    public: 
        App();
        ~App();
        void run();
        static void mouseMoveCallback(GLFWwindow* pWindow, double xpos, double ypos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    private:
        GLFWwindow* _pGLFWwindow;
        MTL::Device* _pDevice;
        CA::MetalLayer* _pMTLlayer;
        NS::Window* _pWindow;
        Renderer* _pRenderer;
        ISimulator* _pSimulator;
}; 

#endif
