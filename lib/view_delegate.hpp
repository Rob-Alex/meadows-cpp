#ifndef view_delegate_hpp
#define view_delegate_hpp

#include "renderer.hpp"
#include <chrono> //for benchmarking

class MTKViewDelegate : public MTK::ViewDelegate
{
    public:
        MTKViewDelegate( MTL::Device* pDevice );
        virtual ~MTKViewDelegate() override;
        virtual void drawInMTKView( MTK::View* pView ) override;

    private:
        Renderer* _pRenderer;
        Simulator* _pSimulator;

    std::chrono::high_resolution_clock::time_point _lastPulseTime; // Last time a pulse was applied
    std::chrono::milliseconds _pulseInterval; 
};

#endif