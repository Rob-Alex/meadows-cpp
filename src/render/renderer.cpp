#include "renderer.hpp"

Renderer::Renderer( MTL::Device* pDevice, ISimulator* pSimulator, CA::MetalLayer* pMTLlayer)
: _pDevice( pDevice->retain() ), _pSimulator(pSimulator), _pMtlLayer(pMTLlayer->retain()), _pCommandQueue(_pDevice->retain()->newCommandQueue()->retain())
{
    buildShaders();
    buildMeshes();
    buildBuffers();
}

Renderer::~Renderer()
{
   if (_pShaderLibrary) {
        _pShaderLibrary->release();
        _pShaderLibrary = nullptr;
    }
    if (_pArgBuffer) {
        _pArgBuffer->release();
        _pArgBuffer = nullptr;
    }
    if (_pVertexPositionsBuffer) {
        _pVertexPositionsBuffer->release();
        _pVertexPositionsBuffer = nullptr;
    }
    if (_pVertexColorsBuffer) {
        _pVertexColorsBuffer->release();
        _pVertexColorsBuffer = nullptr;
    }
    if (_pIndexBuffer) {
        _pIndexBuffer->release();
        _pIndexBuffer = nullptr;
    }
    if (_pCommandQueue) {
        _pCommandQueue->release();
        _pCommandQueue = nullptr;
    }
    if (_pDevice) {
        _pDevice->release();
        _pDevice = nullptr;
    }
}

void Renderer::buildShaders()
{
    NS::Error* pError = nullptr;
    auto filepath = NS::String::string("../shaders/shader.metallib", NS::ASCIIStringEncoding);
    

    _pShaderLibrary = _pDevice->newLibrary(filepath, &pError);
    if (!_pShaderLibrary) {
        __builtin_printf("Error loading shader library: %s\n", pError->localizedDescription()->utf8String());
        assert(false); // Abort execution if library cannot be loaded
    }

    // Retrieve the vertex and fragment functions from the library
    MTL::Function* pVertexFunction = _pShaderLibrary->newFunction(NS::String::string("vertexMain", NS::ASCIIStringEncoding));
    if (!pVertexFunction) {
        __builtin_printf("Failed to load vertex function.\n");
        assert(false);
    }

    MTL::Function* pFragmentFunction = _pShaderLibrary->newFunction(NS::String::string("fragmentMain", NS::ASCIIStringEncoding));
    if (!pFragmentFunction) {
        __builtin_printf("Failed to load fragment function.\n");
        assert(false);
    }

    // Create a render pipeline descriptor
    MTL::RenderPipelineDescriptor* pPipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pPipelineDescriptor->setVertexFunction(pVertexFunction);
    pPipelineDescriptor->setFragmentFunction(pFragmentFunction);

    // Set up the render target pixel format (color attachment)
    pPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

    // Create the render pipeline state object (PSO)
    _pPSO = _pDevice->newRenderPipelineState(pPipelineDescriptor, &pError);
    if (!_pPSO) {
        __builtin_printf("Error creating pipeline state: %s\n", pError->localizedDescription()->utf8String());
        assert(false);
    }

    // Release resources no longer needed
    pPipelineDescriptor->release();
    pVertexFunction->release();
    pFragmentFunction->release();

    __builtin_printf("Shaders built successfully.\n"); 
}

void Renderer::buildMeshes()
{
    // Retrieve grid dimensions
    const size_t gridWidth = _pSimulator->getGridWidth();
    const size_t gridHeight = _pSimulator->getGridHeight();

    // Retrieve simulation data
    float* simulationData = static_cast<float*>(_pSimulator->getSimulationBuffer()->contents());

    // Clear existing mesh data
    _positions.clear();
    _colors.clear();
    _indices.clear();

    // Generate vertex positions and colors dynamically
    for (size_t j = 0; j < gridHeight; ++j) {
        for (size_t i = 0; i < gridWidth; ++i) {
            float value = simulationData[j * gridWidth + i]; // Updated simulation value

            // Map grid coordinates to NDC space
            float x = -1.0f + 2.0f * (i / static_cast<float>(gridWidth - 1));
            float y = -1.0f + 2.0f * (j / static_cast<float>(gridHeight - 1));

            // Add vertex position
            _positions.push_back(simd::make_float3(x, y, 0.0f));

            // Calculate dynamic color based on simulation value
            float red = (sinf(value + 0.5f) * 0.5f + 0.5f); // Map sine wave to [0, 1]
            float green = (cosf(value) * 0.5f + 0.5f);      // Alternate color mapping
            float blue = 0.5f;                              // Constant blue value

            _colors.push_back(simd::make_float3(red, green, blue));
        }
    }

    // Generate index buffer (as before, for a grid)
    for (size_t j = 0; j < gridHeight - 1; ++j) {
        for (size_t i = 0; i < gridWidth - 1; ++i) {
            uint32_t topLeft = j * gridWidth + i;
            uint32_t topRight = topLeft + 1;
            uint32_t bottomLeft = (j + 1) * gridWidth + i;
            uint32_t bottomRight = bottomLeft + 1;

            // First triangle
            _indices.push_back(topLeft);
            _indices.push_back(bottomLeft);
            _indices.push_back(topRight);

            // Second triangle
            _indices.push_back(topRight);
            _indices.push_back(bottomLeft);
            _indices.push_back(bottomRight);
        }
    }
}


void Renderer::buildBuffers()
{
    assert(!_positions.empty() && !_colors.empty() && !_indices.empty());

    const size_t positionsDataSize = _positions.size() * sizeof(simd::float3);
    const size_t colorsDataSize = _colors.size() * sizeof(simd::float3);
    const size_t indicesDataSize = _indices.size() * sizeof(uint32_t);

    // Allocate and copy vertex position data
    _pVertexPositionsBuffer = _pDevice->newBuffer(positionsDataSize, MTL::ResourceStorageModeManaged);
    memcpy(_pVertexPositionsBuffer->contents(), _positions.data(), positionsDataSize);
    _pVertexPositionsBuffer->didModifyRange(NS::Range::Make(0, positionsDataSize));

    // Allocate and copy vertex color data
    _pVertexColorsBuffer = _pDevice->newBuffer(colorsDataSize, MTL::ResourceStorageModeManaged);
    memcpy(_pVertexColorsBuffer->contents(), _colors.data(), colorsDataSize);
    _pVertexColorsBuffer->didModifyRange(NS::Range::Make(0, colorsDataSize));

    // Allocate and copy index buffer data
    _pIndexBuffer = _pDevice->newBuffer(indicesDataSize, MTL::ResourceStorageModeManaged);
    memcpy(_pIndexBuffer->contents(), _indices.data(), indicesDataSize);
    _pIndexBuffer->didModifyRange(NS::Range::Make(0, indicesDataSize));

    // Argument buffer setup
    using NS::StringEncoding::UTF8StringEncoding;
    MTL::Function* pVertexFn = _pShaderLibrary->newFunction(NS::String::string("vertexMain", UTF8StringEncoding));
    MTL::ArgumentEncoder* pArgEncoder = pVertexFn->newArgumentEncoder(0);

    _pArgBuffer = _pDevice->newBuffer(pArgEncoder->encodedLength(), MTL::ResourceStorageModeManaged);
    pArgEncoder->setArgumentBuffer(_pArgBuffer, 0);

    pArgEncoder->setBuffer(_pVertexPositionsBuffer, 0, 0);
    pArgEncoder->setBuffer(_pVertexColorsBuffer, 0, 1);

    _pArgBuffer->didModifyRange(NS::Range::Make(0, _pArgBuffer->length()));

    pVertexFn->release();
    pArgEncoder->release();
}

void Renderer::updateMeshData()
{
    const size_t gridWidth = _pSimulator->getGridWidth();
    const size_t gridHeight = _pSimulator->getGridHeight();

    // Preallocate memory for efficiency
    _positions.resize(gridWidth * gridHeight);
    _colors.resize(gridWidth * gridHeight);

    // Retrieve simulation data
    float* simulationData = static_cast<float*>(_pSimulator->getSimulationBuffer()->contents());

    for (size_t j = 0; j < gridHeight; ++j) {
        for (size_t i = 0; i < gridWidth; ++i) {
            float value = simulationData[j * gridWidth + i];

            float x = -1.0f + 2.0f * (i / static_cast<float>(gridWidth - 1));
            float y = -1.0f + 2.0f * (j / static_cast<float>(gridHeight - 1));

            _positions[j * gridWidth + i] = simd::make_float3(x, y, 0.0f);

            float red = (sinf(value + 0.5f) * 0.5f + 0.5f); //(sinf(value + 0.5f) * 0.5f + 0.5f);
            float green = (cosf(value) * 0.5f + 0.5f);
            float blue = 0.5f; //(cosf(value) * 0.5f + 0.5f); //0.5f;
            _colors[j * gridWidth + i] = simd::make_float3(red, green, blue);
        }
    }
}

void Renderer::updateBuffers()
{
    const size_t positionsDataSize = _positions.size() * sizeof(simd::float3);
    const size_t colorsDataSize = _colors.size() * sizeof(simd::float3);

    assert(_pVertexPositionsBuffer && _pVertexColorsBuffer);

    // Update vertex positions
    memcpy(_pVertexPositionsBuffer->contents(), _positions.data(), positionsDataSize);
    _pVertexPositionsBuffer->didModifyRange(NS::Range::Make(0, positionsDataSize));

    // Update vertex colors
    memcpy(_pVertexColorsBuffer->contents(), _colors.data(), colorsDataSize);
    _pVertexColorsBuffer->didModifyRange(NS::Range::Make(0, colorsDataSize));
} 

void Renderer::draw()
{
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = _pCommandQueue->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = MTL::RenderPassDescriptor::alloc()->init();
    assert(pRpd && "Render pass descriptor is null");


    _pMtlDraw = _pMtlLayer->nextDrawable();
    MTL::RenderPassColorAttachmentDescriptor* pRca = pRpd->colorAttachments()->object(0);
    pRca->setTexture(_pMtlDraw->texture());
    pRca->setLoadAction(MTL::LoadActionClear);
    pRca->setClearColor(MTL::ClearColor(0.3f, 0.3f, 0.3f, 1.0f));
    pRca->setStoreAction(MTL::StoreActionStore);

    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder(pRpd);

    pEnc->setRenderPipelineState(_pPSO);
    pEnc->setVertexBuffer(_pArgBuffer, 0, 0);

    pEnc->useResource(_pVertexPositionsBuffer, MTL::ResourceUsageRead);
    pEnc->useResource(_pVertexColorsBuffer, MTL::ResourceUsageRead);

    // Use indexed draw call
    pEnc->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 
                                _indices.size(), 
                                MTL::IndexType::IndexTypeUInt32, 
                                _pIndexBuffer, 0);

    pEnc->endEncoding();
    pCmd->presentDrawable(_pMtlDraw);
    pCmd->commit();

    pPool->release();
}
