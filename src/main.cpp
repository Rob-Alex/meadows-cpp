//
//  main.cpp
//  Computer
//
//  Created by Robbie Alexander on 22/01/2024.
//
#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "config.hpp"
#include "app_delegate.hpp"
#include <math.h>
#include <assert.h>
#include "mtl_computer.hpp"
#include "cpu_computer.hpp"
#include "benchmarking.hpp"
#include <thread>

void runBenchmarks()
{
     //computing lines 
    MTL::Device *device = MTL::CreateSystemDefaultDevice();
     // Create GPU object
    mtl_computer *computer_mtl = new mtl_computer(device);
   
    //create CPU Object
    cpu_computer *computer_cpu = new cpu_computer();    

    benchmark1D(device, computer_mtl, computer_cpu);
    benchmark2D(device, computer_mtl, computer_cpu);

    delete computer_mtl;
    delete computer_cpu;
}

int main(int argc, const char * argv[]) {

    NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    AppDelegate del;
    NS::Application* pSharedApplication = NS::Application::sharedApplication();

    pSharedApplication->setDelegate( &del );
    
    //std::thread benchmarkThread(runBenchmarks); //for testing the CPU and GPU computers
    //benchmarkThread.join();

    pSharedApplication->run();
        
    pAutoreleasePool->release();

    return 0;
}

