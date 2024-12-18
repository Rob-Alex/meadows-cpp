//
//  mtl_computer.cpp
//  Computer
//
//  Created by Robbie Alexander on 22/01/2024.
//

#include "mtl_computer.hpp"
#include <list>
#include <map>
#include <vector>
#include <iostream>

mtl_computer::mtl_computer(MTL::Device * pDevice, bool loadAll)
: _pDevice(pDevice)
{
    _pCmdQ = _pDevice->newCommandQueue();
    if (!_pCmdQ) {
        __builtin_printf("Failed to create command queue.\n");
        exit(-1);
    }

    if (loadAll) {
        loadAllPipelines();
    }
    
}

mtl_computer::~mtl_computer()
{
    for (auto& [key, pipeline] : functionPipelineMap) {
        pipeline->release();
    }
    _pCmdQ->release();
}

void mtl_computer::loadAllPipelines()
{
    NS::Error* error = nullptr;

    // Load shader library
    auto filepath = NS::String::string("../shaders/compute.metallib", NS::ASCIIStringEncoding);
    MTL::Library* pComputeLibrary = _pDevice->newLibrary(filepath, &error);

    if (!pComputeLibrary) {
        __builtin_printf("Failed to load Metal library.\n");
        exit(-1);
    }

    // Iterate through all functions
    auto fnNames = pComputeLibrary->functionNames();
    for (size_t i = 0; i < fnNames->count(); ++i) {
        auto functionName = fnNames->object<NS::String>(i);
        auto name = functionName->utf8String();
        loadPipeline(pComputeLibrary, name, name);
    }

    pComputeLibrary->release();
}

void mtl_computer::loadPipeline(MTL::Library* library, const std::string& pipelineName, const std::string& functionName)
{
    NS::Error* error = nullptr;

    MTL::Function* function = library->newFunction(NS::String::string(functionName.c_str(), NS::ASCIIStringEncoding));
    if (!function) {
        __builtin_printf("Failed to load function: %s\n", functionName.c_str());
        exit(-1);
    }

    MTL::ComputePipelineState* pipeline = _pDevice->newComputePipelineState(function, &error);
    if (!pipeline) {
        __builtin_printf("Failed to create pipeline for function: %s, Error: %s\n", functionName.c_str(),
                         error ? error->description()->utf8String() : "Unknown error");
        function->release();
        exit(-1);
    }

    functionPipelineMap[pipelineName] = pipeline;

    function->release();
}

void mtl_computer::Blocking2D(std::vector<MTL::Buffer*> buffers, size_t rows, size_t columns, const char* method, void* constants, size_t constantsSize)
{
    MTL::CommandBuffer* pCmdBuff = _pCmdQ->commandBuffer();
    assert(pCmdBuff);

    MTL::ComputeCommandEncoder* pComputeEnc = pCmdBuff->computeCommandEncoder();
    assert(pComputeEnc);

    // Check if pipeline exists
    auto it = functionPipelineMap.find(method);
    if (it == functionPipelineMap.end()) {
        __builtin_printf("Pipeline not found for method: %s", method);
        exit(-1);
    }

    pComputeEnc->setComputePipelineState(functionPipelineMap[method]);

    // Set buffers
    for (size_t i = 0; i < buffers.size(); ++i) {
        pComputeEnc->setBuffer(buffers[i], 0, i);
    }

    // Set optional constant data
    if (constants && constantsSize > 0) {
        pComputeEnc->setBytes(constants, constantsSize, buffers.size());
    }

    // Calculate thread group size
    NS::UInteger maxThreads = functionPipelineMap[method]->maxTotalThreadsPerThreadgroup();
    NS::UInteger threadGroupWidth = std::min(maxThreads, static_cast<NS::UInteger>(rows));
    MTL::Size threadgroupSize = MTL::Size::Make(threadGroupWidth, 1, 1);
    MTL::Size gridSize = MTL::Size::Make(rows, columns, 1);

    // Dispatch compute threads
    pComputeEnc->dispatchThreads(gridSize, threadgroupSize);
    pComputeEnc->endEncoding();

    pCmdBuff->commit();
    pCmdBuff->waitUntilCompleted();
}

void mtl_computer::Blocking1D(std::vector<MTL::Buffer*> buffers, size_t arrayLength, const char* method)
{
    Blocking2D(buffers, arrayLength, 1, method);  
}


void mtl_computer::Add1DArrays(MTL::Buffer* x_array, MTL::Buffer* y_array, MTL::Buffer* r_array, size_t arrayLength)
{
    std::vector<MTL::Buffer*> buffers = {
        x_array, y_array, r_array
    };
    
    const char* method = "add_1D_arrays";
    
    Blocking1D(buffers, arrayLength, method);
}

void mtl_computer::Multiply1DArrays(MTL::Buffer* x_array, MTL::Buffer* y_array, MTL::Buffer* r_array, size_t arrayLength)
{
    std::vector<MTL::Buffer*> buffers = {
        x_array, y_array, r_array
    };
    
    const char* method = "multiply_1D_arrays";
    
    Blocking1D(buffers, arrayLength, method);
}

void mtl_computer::Add2DArrays(MTL::Buffer* A,
                MTL::Buffer* B,
                MTL::Buffer* result,
                size_t rows,
                size_t columns)
{
    std::vector<MTL::Buffer *> buffers = {
        A, B, result
    };
    const char *method = "add_2D_arrays";
    
    Blocking2D(buffers, rows, columns, method);
    
}

void mtl_computer::Multiply2DArrays(MTL::Buffer* A,
                    MTL::Buffer* B,
                    MTL::Buffer* result,
                    size_t rows,
                    size_t columns)
{
    std::vector<MTL::Buffer *> buffers = {
        A, B, result
    };
    const char *method = "multiply_2D_arrays";
    
    Blocking2D(buffers, rows, columns, method);
}
