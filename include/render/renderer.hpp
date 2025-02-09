#ifndef renderer_hpp
#define renderer_hpp

#include "simulator.hpp" 
#include <fstream>
#include <sstream>
#include <string>
#include <simd/simd.h>
#include "config.hpp"

class Renderer
{
    public:
        Renderer( MTL::Device* pDevice, ISimulator* pSimulator, CA::MetalLayer* pMTLlayer);

        ~Renderer();
        void buildMeshes();
        void buildShaders();
        void buildBuffers();
        void updateMeshData();
        void updateBuffers();
        void draw();
        MTL::CommandQueue* getCommandQueue() { return _pCommandQueue; }
    private:
        MTL::Device* _pDevice;
        CA::MetalLayer* _pMtlLayer;
        CA::MetalDrawable* _pMtlDraw;
        MTL::CommandQueue* _pCommandQueue;
        MTL::Library* _pShaderLibrary;
        MTL::RenderPipelineState* _pPSO;
        MTL::Buffer* _pArgBuffer;
        MTL::Buffer* _pVertexPositionsBuffer;
        MTL::Buffer* _pVertexColorsBuffer;      
        MTL::Buffer* _pIndexBuffer;
        ISimulator* _pSimulator;
        std::vector<simd::float3> _positions;
        std::vector<simd::float3> _colors;
        std::vector<uint32_t> _indices; 
};

#endif 
