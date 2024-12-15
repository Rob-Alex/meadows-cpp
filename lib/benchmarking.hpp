//
//  benchmarking.hpp
//  Computer
//
//  Created by Robbie Alexander on 31/01/2024.
//

#ifndef benchmarking_hpp
#define benchmarking_hpp

#include <iostream>
#include <assert.h>
#include <vector>
#include "mtl_computer.hpp"
#include "cpu_computer.hpp"
#include "Metal/Metal.hpp"

//profiling and debugging functions
void generateRandomFloatData(float *dataPtr, 
                                size_t arrayLength);

void generateSequenceFloatData(float *dataPtr, 
                                size_t arrayLength);

bool verifyFloat(float a, 
                    float b, 
                    float epsilon);

bool verifyArray(const float *x, 
                    const float *y,
                    size_t arrayLength);

void zeros(float* a, 
            size_t arrayLength);

void statistics(float *array, 
                size_t length, 
                float &array_mean, 
                float &array_std);

void displayLoadingBar(int currentStep, 
                        int totalSteps);

void benchmark1D(MTL::Device* device, 
                    mtl_computer* computer_mtl, 
                    cpu_computer* computer_cpu);

void benchmark2D(MTL::Device* device, 
                    mtl_computer* computer_mtl,
                    cpu_computer* computer_cpu);

#endif /* benchmarking_hpp */
