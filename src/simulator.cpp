#include "simulator.hpp"

//test simulator interface implementation -------------------------------------------------------------------------------
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
    auto* filepath = NS::String::string("../shaders/compute.metallib", NS::ASCIIStringEncoding);
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
/* 
void TestSimulator::applyPulse(float centerX, float centerY, float intensity) {
    float params[3] = { centerX, centerY, intensity };
    std::vector<MTL::Buffer*> buffers = { _pSimulationBuffer };
    _gpuComputer.Blocking2D(buffers, _gridWidth, _gridHeight, "applyPulse", params, sizeof(params));

    // Ensure buffer is marked as modified
    _pSimulationBuffer->didModifyRange(NS::Range::Make(0, _pSimulationBuffer->length()));
}]*/

//test simulator interface implementation -------------------------------------------------------------------------------

//Finite Difference Time Domain Implementation ----------------------------------------------------------------------------
// TODO: Fix alot
/*
FDTDSolver::FDTDSolver(MTL::Device* pDevice, size_t gridHeight, size_t gridWidth) 
: _pDevice(pDevice), _gridWidth(gridWidth), _gridHeight(gridHeight), _gpuComputer(pDevice)
{
    _pCmdQ = _pDevice->newCommandQueue();
    const size_t bufferSize = gridWidth * gridHeight * sizeof(float);
    _pElectricFieldBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
    _pMagneticFieldBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged); 
    if( !_pElectricFieldBuffer || !_pMagneticFieldBuffer ) 
    {
        __builtin_printf("Error: Failed to allocate buffers");
    }

    reset();
}

FDTDSolver::~FDTDSolver()
{
   _pElectricFieldBuffer->release();
   _pMagneticFieldBuffer->release();
   _pCmdQ->release();
}

void FDTDSolver::initialize()
{
    const size_t bufferSize = _gridWidth * _gridHeight * sizeof(float);
    _pElectricFieldBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
    _pMagneticFieldBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
    loadComputePipelines();

    memset(_pElectricFieldBuffer->contents(), 0, bufferSize);
    _pElectricFieldBuffer->didModifyRange(NS::Range::Make(0, bufferSize));

    memset(_pMagneticFieldBuffer->contents(), 0, bufferSize);
    _pMagneticFieldBuffer->didModifyRange(NS::Range::Make(0, bufferSize));
} 

void FDTDSolver::loadComputePipelines()
{
   NS::Error* pError = nullptr;

    // Load the shader library
    auto* filepath = NS::String::string("../shaders/fdtd.metallib", NS::ASCIIStringEncoding);
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

void FDTDSolver::update(float timeStep)
{
    
}

void FDTDSolver::reset()
{
    memset(_pElectricFieldBuffer->contents(), 0, _gridWidth * _gridHeight * sizeof(float));
    _pElectricFieldBuffer->didModifyRange(NS::Range::Make(0, _pElectricFieldBuffer->length()));

    memset(_pMagneticFieldBuffer->contents(), 0, _gridWidth * _gridWidth * sizeof(float));
    _pMagneticFieldBuffer->didModifyRange(NS::Range::Make(0, _pMagneticFieldBuffer->length()));

    __builtin_printf("FDTD reset: Electric and Magnetic Field Buffers Cleared.\n");
}
*/
// Maxwell Solver Implementation ----------------------------------------------------------------

MaxwellSolver::MaxwellSolver(MTL::Device* pDevice, size_t gridWidth, size_t gridHeight) 
    : _pDevice(pDevice), _gridWidth(gridWidth), _gridHeight(gridHeight), _gpuComputer(pDevice)
{
  _pCmdQ = _pDevice->newCommandQueue(); 
  const size_t bufferSize = gridWidth * gridHeight * sizeof(float);
  _pChargeDensityBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
  _pPotentialBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);

  if ( !_pChargeDensityBuffer || !_pPotentialBuffer )
  {
      __builtin_printf("Error: failed to allocate buffers");
  }

  reset();

}

MaxwellSolver::~MaxwellSolver() noexcept 
{
    _pPotentialBuffer->release();
    _pChargeDensityBuffer->release();
}

void MaxwellSolver::initialize()
{
    const size_t bufferSize = _gridWidth * _gridHeight * sizeof(float);
    _pChargeDensityBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
    _pPotentialBuffer = _pDevice->newBuffer(bufferSize, MTL::ResourceStorageModeManaged);
    loadComputePipelines();

    memset(_pChargeDensityBuffer->contents(), 0, bufferSize);
    _pChargeDensityBuffer->didModifyRange(NS::Range::Make(0, bufferSize));

    memset(_pPotentialBuffer->contents(), 0, bufferSize);
    _pPotentialBuffer->didModifyRange(NS::Range::Make(0, bufferSize));
}

void MaxwellSolver::loadComputePipelines()
{
    NS::Error* pError = nullptr;

    // Load the shader library
    auto* filepath = NS::String::string("../shaders/compute.metallib", NS::ASCIIStringEncoding);
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

void MaxwellSolver::update(float timeStep) 
{

}

void MaxwellSolver::reset()
{
    const size_t bufferSize = _gridHeight * _gridWidth * sizeof(float);
    memset(_pChargeDensityBuffer->contents(), 0, bufferSize);
    _pChargeDensityBuffer->didModifyRange(NS::Range::Make(0, bufferSize));

    memset(_pPotentialBuffer->contents(), 0, bufferSize);
    _pPotentialBuffer->didModifyRange(NS::Range::Make(0, bufferSize));   
    __builtin_printf("Simulation reset: buffers cleared"); 
}
