#ifndef renderer_hpp
#define renderer_hpp

#include "simulator.hpp" 
#include <fstream>
#include <sstream>
#include <string>
#include <simd/simd.h>

class Renderer
{
    public:
        Renderer( MTL::Device* pDevice , Simulator* pSimulator);
        ~Renderer();
        void buildMeshes();
        void buildShaders();
        void buildBuffers();
        void draw( MTK::View* pView );
    private:
        MTL::Device* _pDevice;
        MTL::CommandQueue* _pCommandQueue;
        MTL::Library* _pShaderLibrary;
        MTL::RenderPipelineState* _pPSO;
        MTL::Buffer* _pArgBuffer;
        MTL::Buffer* _pVertexPositionsBuffer;
        MTL::Buffer* _pVertexColorsBuffer;      
        MTL::Buffer* _pIndexBuffer;
        Simulator* _pSimulator;
        std::vector<simd::float3> _positions;
        std::vector<simd::float3> _colors;
};

#endif 