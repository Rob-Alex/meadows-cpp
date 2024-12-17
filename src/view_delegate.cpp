#include "view_delegate.hpp"

MTKViewDelegate::MTKViewDelegate( MTL::Device* pDevice )
: MTK::ViewDelegate()
{
    _pSimulator = new Simulator(pDevice, 100, 100); //init with grid dimensions 
    _pRenderer = new Renderer(pDevice, _pSimulator);\

}

MTKViewDelegate::~MTKViewDelegate()
{
    delete _pRenderer;
    delete _pSimulator;
}

void MTKViewDelegate::drawInMTKView(MTK::View* pView)
{
    // Calculate time elapsed
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime).count() / 1e6f;

    // Update simulation with cumulative time
    _pSimulator->updateSimulation(timeElapsed);

    // Update renderer with the latest simulation data
    _pRenderer->updateMeshData();
    _pRenderer->updateBuffers();

    // Draw the updated frame
    _pRenderer->draw(pView);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - currentTime).count();
    __builtin_printf("Frame Time: %lld μs\n", frameDuration);
}