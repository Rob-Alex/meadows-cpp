//
//  benchmarking.cpp
//  Computer
//
//  Created by Robbie Alexander on 31/01/2024.
//

#include "benchmarking.hpp"

//profiling and debugging functions
void generateRandomFloatData(float *dataPtr, size_t arrayLength)
{
    for (unsigned long index = 0; index < arrayLength; index++)
    {
        dataPtr[index] = (float)rand() / (float)(RAND_MAX);
    }
}

bool verifyFloat(float a, float b, float epsilon)
{
    return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool verifyArray(const float *x, const float *y, size_t arrayLength)
{
    for(unsigned long index = 0; index < arrayLength; index++)
    {
        //printf("Result: index=%lu x=%e vs y=%e. \n", index, x[index], y[index]);
        if(!verifyFloat(x[index], y[index], std::numeric_limits<float>::epsilon()))
        {
            printf("Error: index=%lu x=%e vs y=%e. \n", index, x[index], y[index]);
            return false;
        }
    }
    return true;
}

void zeros(float* a, size_t arrayLength)
{
    for(unsigned long index = 0; index < arrayLength; index++)
    {
        a[index] = 0;
    }
}

void statistics(float *array, size_t length, float &array_mean, float &array_std)
{
    // Compute mean and standard deviation serially, template function

    array_mean = 0;
    for (size_t repeat = 0; repeat < length; repeat++)
    {
        array_mean += array[repeat];
    }
    array_mean /= length;

    array_std = 0;
    for (size_t repeat = 0; repeat < length; repeat++)
    {
        array_std += pow(array_mean - array[repeat], 2.0);
    }
    array_std /= length;
    array_std = pow(array_std, 0.5);
}

typedef std::chrono::microseconds time_unit;
auto unit_name = "µs";
//for benchmarking
size_t repeats = 500;

// Function to display a loading bar
void displayLoadingBar(int currentStep, int totalSteps) {
    const int barWidth = 50; // Width of the loading bar
        // Calculate progress
        float progress = static_cast<float>(currentStep) / totalSteps;
        int pos = static_cast<int>(barWidth * progress);

        // Print the loading bar
        std::cout << "[";
        for (int j = 0; j < barWidth; ++j) {
            if (j < pos)
                std::cout << "=";
            else if (j == pos)
                std::cout << ">";
            else
                std::cout << " ";
        }
        std::cout << "] " << static_cast<int>(progress * 100) << "%\r"; // Overwrite the current line
        std::cout.flush();
        if (currentStep == totalSteps) {  std::cout << std::endl; }
}

void benchmark1D(MTL::Device* device, mtl_computer* computer_mtl, cpu_computer* computer_cpu)
{
    
    //1D configuration
    const unsigned int ARRAY_LENGTH = 1000000;
    const unsigned int BUFFER_SIZE = ARRAY_LENGTH * sizeof(float);
    
    device = MTL::CreateSystemDefaultDevice();
    
    std::cout << "Device: " << device->name()->utf8String() << std::endl;
    std::cout << "Array size: " << ARRAY_LENGTH << std::endl;
    
    MTL::Buffer *a_MTL = device->newBuffer(BUFFER_SIZE, MTL::ResourceStorageModeManaged);
    MTL::Buffer *b_MTL = device->newBuffer(BUFFER_SIZE, MTL::ResourceStorageModeManaged);
    MTL::Buffer *c_MTL = device->newBuffer(BUFFER_SIZE, MTL::ResourceStorageModeManaged);
    
    // Get a C++-style reference to the buffer
    auto a_CPP = (float *)a_MTL->contents();
    auto b_CPP = (float *)b_MTL->contents();
    auto c_CPP = (float *)c_MTL->contents();
    
    auto c_VER = new float[ARRAY_LENGTH];

    generateRandomFloatData(a_CPP, ARRAY_LENGTH);
    generateRandomFloatData(b_CPP, ARRAY_LENGTH);
    zeros(c_CPP, ARRAY_LENGTH);
     
    // 1D add verification
    computer_mtl->Add1DArrays(a_MTL, b_MTL, c_MTL, ARRAY_LENGTH);
    computer_cpu->Add1DArrays(a_CPP, b_CPP, c_VER, ARRAY_LENGTH);
    assert(verifyArray(c_CPP, c_VER, ARRAY_LENGTH));
    zeros(c_CPP, ARRAY_LENGTH);
    std::cout << "Add1DArrays: mtl_computer result is equal to cpu_computer result. \n";
    
    //1D multiply verification
    computer_mtl->Multiply1DArrays(a_MTL, b_MTL, c_MTL, ARRAY_LENGTH);
    computer_cpu->Multiply1DArrays(a_CPP, b_CPP, c_VER, ARRAY_LENGTH);
    assert(verifyArray(c_CPP, c_VER, ARRAY_LENGTH));
    zeros(c_CPP, ARRAY_LENGTH);
    std::cout << "Multiply1DArrays: mtl_computer result is equal to cpu_computer result. \n";
    
    //add 1D array Benchmarking --------------------------------------------------
    std::cout << "Benchmarking Add_1D_Arrays ... \n";
    
    float *durations = new float[repeats];
    float array_mean;
    float array_std;

    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_mtl->Add1DArrays(a_MTL, b_MTL, c_MTL, ARRAY_LENGTH);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "GPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_cpu->Add1DArrays(a_CPP, b_CPP, c_CPP, ARRAY_LENGTH);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "CPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    //multiply 1D array Benchmarking --------------------------------------------------
    std::cout << "Benchmarking Multiply_1D_Arrays ... \n";
    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_mtl->Multiply1DArrays(a_MTL, b_MTL, c_MTL, ARRAY_LENGTH);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "GPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_cpu->Multiply1DArrays(a_CPP, b_CPP, c_CPP, ARRAY_LENGTH);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "CPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    a_MTL->release();
    b_MTL->release();
    c_MTL->release();
}

void benchmark2D(MTL::Device* device, mtl_computer* computer_mtl, cpu_computer* computer_cpu)
{
    //2D configuration
    const unsigned long SIZE = 200;
    const unsigned long ROWS = SIZE;
    const unsigned long COLUMNS = SIZE;
    const unsigned long ARRAY_LENGTH = ROWS * COLUMNS;
    const unsigned long BUFFER_SIZE = ARRAY_LENGTH * sizeof(float);
    
    device = MTL::CreateSystemDefaultDevice();
    
    std::cout << "Device: " << device->name()->utf8String() << std::endl;
    std::cout << "Matrix Dimensions: " << ROWS << "x" << COLUMNS << std::endl;
    
    MTL::Buffer *a_MTL = device->newBuffer(BUFFER_SIZE, MTL::ResourceStorageModeManaged);
    MTL::Buffer *b_MTL = device->newBuffer(BUFFER_SIZE, MTL::ResourceStorageModeManaged);
    MTL::Buffer *c_MTL = device->newBuffer(BUFFER_SIZE, MTL::ResourceStorageModeManaged);
    
    // Get a C++-style reference to the buffer
    auto a_CPP = (float *)a_MTL->contents();
    auto b_CPP = (float *)b_MTL->contents();
    auto c_CPP = (float *)c_MTL->contents();
    
    auto c_VER = new float[ARRAY_LENGTH];

    generateRandomFloatData(a_CPP, ARRAY_LENGTH);
    generateRandomFloatData(b_CPP, ARRAY_LENGTH);
    zeros(c_CPP, ARRAY_LENGTH);

//    for(unsigned long index = 0; index < ARRAY_LENGTH; index++)
//    {
//        std::cout << "A[" << index << "]: " << a_CPP[index] << "\t\t B[" << index << "]: " << b_CPP[index] << std::endl;
//    }
    
   
    
    // 2D add verification
    computer_mtl->Add2DArrays(a_MTL, b_MTL, c_MTL, ROWS, COLUMNS);
    computer_cpu->Add2DArrays(a_CPP, b_CPP, c_VER, ROWS, COLUMNS);
    assert(verifyArray(c_CPP, c_VER, ARRAY_LENGTH));
    zeros(c_CPP, ARRAY_LENGTH);
    std::cout << "Add2DArrays: mtl_computer result is equal to cpu_computer result. \n";
    
    //1D multiply verification
    computer_mtl->Multiply2DArrays(a_MTL, b_MTL, c_MTL, ROWS, COLUMNS);
    computer_cpu->Multiply2DArrays(a_CPP, b_CPP, c_VER, ROWS, COLUMNS);
    assert(verifyArray(c_CPP, c_VER, ARRAY_LENGTH));
    zeros(c_CPP, ARRAY_LENGTH);
    std::cout << "Multiply2DArrays: mtl_computer result is equal to cpu_computer result. \n";
    
    //add 1D array Benchmarking --------------------------------------------------
    std::cout << "Benchmarking Add_2D_Arrays ... \n";
    
    float *durations = new float[repeats];
    float array_mean;
    float array_std;

    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_mtl->Add2DArrays(a_MTL, b_MTL, c_MTL, ROWS, COLUMNS);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "GPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_cpu->Add2DArrays(a_CPP, b_CPP, c_CPP, ROWS, COLUMNS);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "CPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    //multiply 1D array Benchmarking --------------------------------------------------
    std::cout << "Benchmarking Multiply_2D_Arrays ... \n";
    
    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_mtl->Multiply2DArrays(a_MTL, b_MTL, c_MTL, ROWS, COLUMNS);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "GPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    for(size_t repeat = 0; repeat < repeats; repeat++)
    {
        displayLoadingBar(repeat, repeats-1);
        auto start = std::chrono::high_resolution_clock::now();
        computer_cpu->Multiply2DArrays(a_CPP, b_CPP, c_CPP, ROWS, COLUMNS);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop - start).count();
        durations[repeat] = duration;
    }
    statistics(durations, repeats, array_mean, array_std);
    std::cout << "CPU: \t\t" << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl;
    
    a_MTL->release();
    b_MTL->release();
    c_MTL->release();
}
