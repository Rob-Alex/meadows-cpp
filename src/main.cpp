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


#include "config.hpp"
#include "app.hpp"


int main(int argc, const char * argv[]) {

    NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();

    App* app = new App();
    app->run();
    
    delete app;

    pAutoreleasePool->release();
    return 0;
}

