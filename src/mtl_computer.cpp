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

mtl_computer::mtl_computer(MTL::Device * Device)
{
    _pDevice = Device;
    NS::Error* error = nullptr;
    
    // Load the shader files with .metal from the project
    auto filepath = NS::String::string("../shaders/compute.metallib", NS::ASCIIStringEncoding);
    
    MTL::Library *pComputeLibrary = _pDevice->newLibrary(filepath, &error);
    
    if (!pComputeLibrary) {
        std::cerr << "Failed to find the default library.\n";
        exit(-1);
    }
    
    //get functions from shader library
    auto fnNames = pComputeLibrary->functionNames();
    std::cout << "Functions from 'compute.metallib' loaded. \n";
    
    for (size_t i = 0; i < fnNames->count(); i++)
    {
        auto names_nsstring = fnNames->object(i)->description();
        auto names_utf8 = names_nsstring->utf8String();
        
        //Show available functions
        std::cout << names_utf8 << std::endl;
        
        // Load each function into map through loop
        functionMap[names_utf8] = (pComputeLibrary->newFunction(names_nsstring));
        
        //create pipeline from function
        functionPipelineMap[names_utf8] = _pDevice->newComputePipelineState(functionMap[names_utf8], &error);
        
        if (!functionPipelineMap[names_utf8])
        {
            std::cerr << "Failed to create a PSO for " << names_utf8 << ", error " << error->description()->utf8String() << std::endl;
            exit(-1);
        }
    }
    
    _pCmdQ = _pDevice->newCommandQueue();
    if(!_pCmdQ)
    {
        std::cerr << "Failed to find command queue. \n";
        exit(-1);
    }
    
}

void mtl_computer::Blocking1D(std::vector<MTL::Buffer*> buffers, size_t arrayLength, const char* method)
{
    MTL::CommandBuffer* pCmdBuff = _pCmdQ->commandBuffer();
    assert(pCmdBuff);
    
    MTL::ComputeCommandEncoder* pComputeEnc = pCmdBuff->computeCommandEncoder();
    assert(pComputeEnc);
    
    pComputeEnc->setComputePipelineState(functionPipelineMap[method]);
    for (std::size_t i = 0; i < buffers.size(); ++i)
    {
        pComputeEnc->setBuffer(buffers[i], 0, i);
    }
    
    NS::UInteger threadGroupSize = functionPipelineMap[method]->maxTotalThreadsPerThreadgroup();
    if (threadGroupSize > arrayLength) threadGroupSize = arrayLength;
    
    //aspect ratio of kernel operation 1:1
    MTL::Size threadgroupSize = MTL::Size::Make(threadGroupSize, 1, 1);
    //Kernel operation on row vector
    MTL::Size gridSize = MTL::Size::Make(arrayLength, 1, 1);
   
    // encode compute command
    pComputeEnc->dispatchThreads(gridSize, threadgroupSize);
    pComputeEnc->endEncoding();
    
    pCmdBuff->commit();
    pCmdBuff->waitUntilCompleted();
    
}

void mtl_computer::Blocking2D(std::vector<MTL::Buffer*> buffers, size_t rows, size_t columns, const char* method)
{
    MTL::CommandBuffer* pCmdBuff = _pCmdQ->commandBuffer();
    assert(pCmdBuff);
    
    MTL::ComputeCommandEncoder* pComputeEnc = pCmdBuff->computeCommandEncoder();
    assert(pComputeEnc);
    
    pComputeEnc->setComputePipelineState(functionPipelineMap[method]);
    for (std::size_t i = 0; i < buffers.size(); ++i)
    {
        pComputeEnc->setBuffer(buffers[i], 0, i);
    }
    NS::UInteger threadGroupSize = functionPipelineMap[method]->maxTotalThreadsPerThreadgroup();
    if (threadGroupSize > rows ) threadGroupSize = rows;
    
    // Kernel operation on a 2D Matrix (width, height, depth
    MTL::Size threadgroupSize = MTL::Size::Make(1, threadGroupSize/1 , 1);
    
    MTL::Size gridSize = MTL::Size::Make(rows, columns, 1);
    
    //encode the compute command
    pComputeEnc->dispatchThreads(gridSize, threadgroupSize);
    pComputeEnc->endEncoding();
    
    pCmdBuff->commit();
    pCmdBuff->waitUntilCompleted();
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

mtl_computer::~mtl_computer()
{
    _pCmdQ->release();
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
