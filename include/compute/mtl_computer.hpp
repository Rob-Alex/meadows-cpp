//
//  mtl_computer.hpp
//  Computer
//
//  Created by Robbie Alexander on 22/01/2024.
//

#ifndef mtl_computer_hpp
#define mtl_computer_hpp

#include <Metal/Metal.hpp>

#include "map"

class mtl_computer {
public:
    MTL::Device* _pDevice;
    
    mtl_computer(MTL::Device*, bool loadAll=true);
    ~mtl_computer();

//Pipeline Management 
    void loadPipeline(MTL::Library*, const std::string& pipelineName, const std::string& functionName);
    void loadAllPipelines();

    void Blocking1D(std::vector<MTL::Buffer*>,size_t, const char*);
    void Blocking2D(std::vector<MTL::Buffer*>, size_t, size_t, const char*, void* constants = nullptr, size_t constantsSize = 0);
// 1D manipulation ---------------------------------
    void Add1DArrays(MTL::Buffer*, MTL::Buffer*, MTL::Buffer*, size_t); 
    void Multiply1DArrays(MTL::Buffer*, MTL::Buffer*, MTL::Buffer*, size_t);
    
// 2D manipulation ---------------------------------
    void Add2DArrays(MTL::Buffer*, MTL::Buffer*, MTL::Buffer*, size_t, size_t);
    void Multiply2DArrays(MTL::Buffer*, MTL::Buffer*, MTL::Buffer*, size_t, size_t);
    
private:
    std::map<std::string, MTL::Function*> functionMap;
    std::map<std::string, MTL::ComputePipelineState*> functionPipelineMap;
    
    MTL::CommandQueue* _pCmdQ;
};

#endif /* mtl_computer_hpp */
