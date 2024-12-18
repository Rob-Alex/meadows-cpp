#include "view_delegate.hpp"

MTKViewDelegate::MTKViewDelegate( MTL::Device* pDevice )
: MTK::ViewDelegate()
{
    _pSimulator = new TestSimulator(pDevice, 100, 100); //init with grid dimensions 
    _pSimulator->initialize();
    _pRenderer = new Renderer(pDevice, _pSimulator);\

}

MTKViewDelegate::~MTKViewDelegate()
{
    delete _pRenderer;
    delete _pSimulator;
}

void MTKViewDelegate::drawInMTKView(MTK::View* pView)
{
    // Static variables to calculate FPS
    static auto lastFPSUpdateTime = std::chrono::high_resolution_clock::now();
    static size_t frameCount = 0;
    static double frameTimeAccumulator = 0.0;

    // Calculate time elapsed
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime).count() / 1e6f;

    // Update simulation with cumulative time
    _pSimulator->update(timeElapsed);

    // Update renderer with the latest simulation data
    _pRenderer->updateMeshData();
    _pRenderer->updateBuffers();

    // Draw the updated frame
    _pRenderer->draw(pView);

    // Measure frame duration
    auto endTime = std::chrono::high_resolution_clock::now();
    double frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - currentTime).count() / 1e6;

    // Accumulate frame time and increment frame count
    frameTimeAccumulator += frameDuration;
    frameCount++;

    // Check if 1 second has passed
    auto elapsedSinceLastUpdate = std::chrono::duration_cast<std::chrono::seconds>(endTime - lastFPSUpdateTime).count();
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
    }
}

