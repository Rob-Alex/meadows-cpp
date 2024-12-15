#include "simulator.hpp"

Simulator::Simulator(MTL::Device* pDevice, size_t gridWidth, size_t gridHeight)
: _pDevice(pDevice->retain()), _gridWidth(gridWidth), _gridHeight(gridHeight)
{
    const size_t bufferSize = gridWidth * gridHeight * sizeof(float);
    _pSimulationBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
}

Simulator::~Simulator()
{
    _pSimulationBuffer->release();
    _pDevice->release();
}

void Simulator::updateSimulation()
{
    static auto startTime = std::chrono::steady_clock::now(); // Start time
    auto currentTime = std::chrono::steady_clock::now();
    float timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

    float* data = static_cast<float*>(_pSimulationBuffer->contents());

    for (size_t j = 0; j < _gridHeight; ++j) {
        for (size_t i = 0; i < _gridWidth; ++i) {
            // Simulation scalar value as a sine wave with time and position dependency
            float value = sinf(static_cast<float>(i) * 0.1f + static_cast<float>(j) * 0.1f + timeElapsed);

            // Update the simulation buffer
            data[j * _gridWidth + i] = value;

            // Optionally, map the value to RGB color components
            // This could be passed separately or calculated later in buildMeshes
        }
    }

    _pSimulationBuffer->didModifyRange(NS::Range::Make(0, _pSimulationBuffer->length()));
}


MTL::Buffer* Simulator::getSimulationBuffer() const
{
    return _pSimulationBuffer;
}