#ifndef view_delegate_hpp
#define view_delegate_hpp

#include "renderer.hpp"

class MTKViewDelegate : public MTK::ViewDelegate
{
    public:
        MTKViewDelegate( MTL::Device* pDevice );
        virtual ~MTKViewDelegate() override;
        virtual void drawInMTKView( MTK::View* pView ) override;

    private:
        Renderer* _pRenderer;
        Simulator* _pSimulator;
};

#endif