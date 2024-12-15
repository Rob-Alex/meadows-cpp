#include "view_delegate.hpp"

MTKViewDelegate::MTKViewDelegate( MTL::Device* pDevice )
: MTK::ViewDelegate()
{
    _pSimulator = new Simulator(pDevice, 100, 100); //init with grid dimensions 
    _pRenderer = new Renderer(pDevice, _pSimulator);
}

MTKViewDelegate::~MTKViewDelegate()
{
    delete _pRenderer;
    delete _pSimulator;
}

void MTKViewDelegate::drawInMTKView( MTK::View* pView )
{
    _pSimulator->updateSimulation();
    _pRenderer->buildMeshes();
    _pRenderer->buildBuffers();
    _pRenderer->draw( pView );
}
