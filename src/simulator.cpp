#include "simulator.hpp"

Simulator::Simulator(MTL::Device* pDevice, size_t gridWidth, size_t gridHeight)
: _pDevice(pDevice->retain()), _gridWidth(gridWidth), _gridHeight(gridHeight)
{
    _pCmdQ = _pDevice->newCommandQueue();
    const size_t bufferSize = gridWidth * gridHeight * sizeof(float);
    _pSimulationBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
    loadComputeShaders("../shaders/compute.metallib");
}

Simulator::~Simulator()
{
    for (auto& [name, pipeline] : _pComputePipelines)
    {
        pipeline->release();   
    }
    _pSimulationBuffer->release();
    _pCmdQ->release();
    _pDevice->release();
}

void Simulator::loadComputeShaders(const std::string& shaderPath)
{
    NS::Error* error = nullptr;
    auto filepath = NS::String::string(shaderPath.c_str(), NS::ASCIIStringEncoding);
    MTL::Library* pLibrary = _pDevice->newLibrary(filepath, &error);

    if (!pLibrary) {
        __builtin_printf("Failed to load compute shader library: %s \n", shaderPath.c_str());
        exit(-1);
    }

    // Iterate through functions in the shader library
    auto fnNames = pLibrary->functionNames();
    for (size_t i = 0; i < fnNames->count(); i++) {
        auto functionName = fnNames->object<NS::String>(i); // Cast to NS::String
        auto name = functionName->utf8String(); // Access utf8String
        
        _pComputePipelines[name] = _pDevice->newComputePipelineState(pLibrary->newFunction(functionName), &error);

        __builtin_printf("Loaded: %s \n", name );

        if (!_pComputePipelines[name]) {
            __builtin_printf("Failed to create compute pipeline state for function: %s \n", name);
            exit(-1);
        }
    }
}

void Simulator::applyPulse(float centerX, float centerY, float timeElapsed)
{
    MTL::CommandBuffer* pCommandBuffer = _pCmdQ->commandBuffer();
    MTL::ComputeCommandEncoder* pEncoder = pCommandBuffer->computeCommandEncoder();

    // Set the pipeline for applying the pulse
    auto pipeline = _pComputePipelines["applyPulse"];
    pEncoder->setComputePipelineState(pipeline);

    // Bind the simulation buffer and pulse parameters
    pEncoder->setBuffer(_pSimulationBuffer, 0, 0);
    float params[3] = {centerX, centerY, timeElapsed};
    pEncoder->setBytes(params, sizeof(params), 1);

    // Dispatch threads
    MTL::Size gridSize = MTL::Size::Make(_gridWidth, _gridHeight, 1);
    MTL::Size threadGroupSize = MTL::Size::Make(16, 16, 1); // Tuned for GPU hardware
    pEncoder->dispatchThreads(gridSize, threadGroupSize);

    pEncoder->endEncoding();
    pCommandBuffer->commit();
    pCommandBuffer->waitUntilCompleted();
}

void Simulator::dispatchCompute2D(const char* method, MTL::Buffer* buffer, void* constants, size_t constantsSize)
{
    MTL::CommandBuffer* pCommandBuffer = _pCmdQ->commandBuffer();
    assert(pCommandBuffer);

    MTL::ComputeCommandEncoder* pEncoder = pCommandBuffer->computeCommandEncoder();
    assert(pEncoder);

    auto pipeline = _pComputePipelines[method];
    assert(pipeline);
    pEncoder->setComputePipelineState(pipeline);

    // Bind the primary buffer and constants
    pEncoder->setBuffer(buffer, 0, 0);
    if (constants && constantsSize > 0) {
        pEncoder->setBytes(constants, constantsSize, 1);
    }

    // Calculate thread groups
    NS::UInteger maxThreads = pipeline->maxTotalThreadsPerThreadgroup();
    NS::UInteger threadGroupWidth = std::min(maxThreads, static_cast<NS::UInteger>(_gridWidth));
    NS::UInteger threadGroupHeight = std::min(maxThreads / threadGroupWidth, static_cast<NS::UInteger>(_gridHeight));

    MTL::Size threadGroupSize = MTL::Size::Make(threadGroupWidth, threadGroupHeight, 1);
    MTL::Size gridSize = MTL::Size::Make(_gridWidth, _gridHeight, 1);

    // Dispatch the compute task
    pEncoder->dispatchThreads(gridSize, threadGroupSize);
    pEncoder->endEncoding();

    pCommandBuffer->commit();
    pCommandBuffer->waitUntilCompleted(); // Optional
}

void Simulator::updateSimulation(float timeElapsed)
{
    dispatchCompute2D("updateGrid", _pSimulationBuffer, &timeElapsed, sizeof(timeElapsed));
}
