#include "renderer.hpp"

Renderer::Renderer( MTL::Device* pDevice, Simulator* pSimulator )
: _pDevice( pDevice->retain() ), _pSimulator(pSimulator)
{
    _pCommandQueue = _pDevice->newCommandQueue();
    buildShaders();
    buildMeshes();
    buildBuffers();
}

Renderer::~Renderer()
{
    _pShaderLibrary->release();
    _pArgBuffer->release();
    _pVertexPositionsBuffer->release();
    _pVertexColorsBuffer->release();
    _pIndexBuffer->release();
    _pCommandQueue->release();
    _pDevice->release();
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
    //tested working hardcoded data
    _positions = {
        simd::make_float3(-0.8f, 0.8f, 0.0f),
        simd::make_float3(0.0f, -0.8f, 0.0f),
        simd::make_float3(0.8f, 0.8f, 0.0f)
    };
    _colors = {
        simd::make_float3(1.0f, 0.3f, 0.2f),
        simd::make_float3(0.8f, 1.0f, 0.0f),
        simd::make_float3(0.8f, 0.0f, 1.0f)
    };
}

void Renderer::buildBuffers()
{
    assert(!_positions.empty() && !_colors.empty());

    const size_t positionsDataSize = _positions.size() * sizeof(simd::float3);
    const size_t colorsDataSize = _colors.size() * sizeof(simd::float3);

    _pVertexPositionsBuffer = _pDevice->newBuffer(positionsDataSize, MTL::ResourceStorageModeManaged);
    _pVertexColorsBuffer = _pDevice->newBuffer(colorsDataSize, MTL::ResourceStorageModeManaged);

    memcpy(_pVertexPositionsBuffer->contents(), _positions.data(), positionsDataSize);
    memcpy(_pVertexColorsBuffer->contents(), _colors.data(), colorsDataSize);

    _pVertexPositionsBuffer->didModifyRange(NS::Range::Make(0, positionsDataSize));
    _pVertexColorsBuffer->didModifyRange(NS::Range::Make(0, colorsDataSize));

    // Argument buffer setup
    using NS::StringEncoding::UTF8StringEncoding;
    assert(_pShaderLibrary);

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



void Renderer::draw( MTK::View* pView )
{
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = _pCommandQueue->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    assert(pRpd && "Render pass descriptor is null");
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder(pRpd);

    pEnc->setRenderPipelineState( _pPSO );
    pEnc->setVertexBuffer( _pArgBuffer, 0, 0 );
    pEnc->useResource( _pVertexPositionsBuffer, MTL::ResourceUsageRead );
    pEnc->useResource( _pVertexColorsBuffer, MTL::ResourceUsageRead );
    pEnc->drawPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3) );

    pEnc->endEncoding();
    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();
}