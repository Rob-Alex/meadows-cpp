//
//  main.cpp
//  Computer
//
//  Created by Robbie Alexander on 22/01/2024.
//
//
#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "app_delegate.hpp"


int main(int argc, const char * argv[]) {

    NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    AppDelegate del;
    NS::Application* pSharedApplication = NS::Application::sharedApplication();

    pSharedApplication->setDelegate( &del );

    pSharedApplication->run();

    // This is a comments
    // this is another commment
    
    pAutoreleasePool->release();
    return 0;
}

