#include "view_delegate.hpp"

MTKViewDelegate::MTKViewDelegate( MTL::Device* pDevice )
: MTK::ViewDelegate()
{
    _pSimulator = new Simulator(pDevice, 10, 10); //init with grid dimensions 
    _pRenderer = new Renderer(pDevice, _pSimulator);
}

MTKViewDelegate::~MTKViewDelegate()
{
    delete _pRenderer;
    delete _pSimulator;
}

void MTKViewDelegate::drawInMTKView( MTK::View* pView )
{
    _pRenderer->draw( pView );
}
