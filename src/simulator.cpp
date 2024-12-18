#include "simulator.hpp"

//deprecated ------------------------------------------------------------------------------------------------------------
Simulator::Simulator(MTL::Device* pDevice, size_t gridWidth, size_t gridHeight)
: _pDevice(pDevice->retain()), _gridWidth(gridWidth), _gridHeight(gridHeight), _gpuComputer(pDevice)
{
    _pCmdQ = _pDevice->newCommandQueue();
    const size_t bufferSize = gridWidth * gridHeight * sizeof(float);
    _pSimulationBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
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

void Simulator::updateSimulation(float timeElapsed)
{
    // Prepare constant data (timeElapsed)
    std::vector<MTL::Buffer*> buffers = { _pSimulationBuffer };
    _gpuComputer.Blocking2D(buffers, _gridWidth, _gridHeight, "updateGrid", &timeElapsed, sizeof(timeElapsed));
}

void Simulator::applyPulse(float centerX, float centerY, float timeElapsed)
{
    // Prepare pulse parameters
    float params[3] = { centerX, centerY, timeElapsed };
    std::vector<MTL::Buffer*> buffers = { _pSimulationBuffer };

    _gpuComputer.Blocking2D(buffers, _gridWidth, _gridHeight, "applyPulse", params, sizeof(params));
}
//deprecated ------------------------------------------------------------------------------------------------------------

//test simulator interface implementation 
TestSimulator::TestSimulator(MTL::Device* pDevice, size_t gridWidth, size_t gridHeight) 
: _pDevice(pDevice), _gridWidth(gridWidth), _gridHeight(gridHeight), _gpuComputer(pDevice)
{
    _pCmdQ = _pDevice->newCommandQueue();
}

TestSimulator::~TestSimulator()
{
    _pSimulationBuffer->release();
    _pCmdQ->release();
}

void TestSimulator::initialize()
{
    const size_t bufferSize = _gridWidth * _gridHeight * sizeof(float);
    _pSimulationBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);

    loadComputePipelines();

     memset(_pSimulationBuffer->contents(), 0, bufferSize);
    _pSimulationBuffer->didModifyRange(NS::Range::Make(0, bufferSize));
}

void TestSimulator::reset()
{
    // Clear the simulation buffer by setting all values to 0
    memset(_pSimulationBuffer->contents(), 0, _gridWidth * _gridHeight * sizeof(float));
    _pSimulationBuffer->didModifyRange(NS::Range::Make(0, _pSimulationBuffer->length()));

    __builtin_printf("TestSimulator reset: Simulation buffer cleared.\n");
}

void TestSimulator::loadComputePipelines()
{
   NS::Error* pError = nullptr;

    // Load the shader library
    auto filepath = NS::String::string("../shaders/compute.metallib", NS::ASCIIStringEncoding);
    MTL::Library* pLibrary = _pDevice->newLibrary(filepath, &pError);
    if (!pLibrary) {
        __builtin_printf("Failed to load Metal library. Error: %s\n",
                        pError ? pError->description()->utf8String() : "Unknown error");
        exit(-1);
    }

    // Load specific compute pipelines
    _gpuComputer.loadPipeline(pLibrary, "updateGrid", "updateGrid");
    _gpuComputer.loadPipeline(pLibrary, "applyPulse", "applyPulse");

    pLibrary->release(); // Release the library after pipelines are loaded
}

MTL::Buffer* TestSimulator::getSimulationBuffer() const
{
    return _pSimulationBuffer; // Return the simulation buffer
}

void TestSimulator::update(float timeStep)
{
    std::vector<MTL::Buffer*> buffers = { _pSimulationBuffer };
    _gpuComputer.Blocking2D(buffers, _gridWidth, _gridHeight, "updateGrid", &timeStep, sizeof(timeStep));
}