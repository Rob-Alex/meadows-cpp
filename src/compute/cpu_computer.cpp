//
//  cpu_computer.cpp
//  Computer
//
//  Created by Robbie Alexander on 31/01/2024.
//

#include "cpu_computer.hpp"

cpu_computer::cpu_computer()
{
    
}

cpu_computer::~cpu_computer()
{
    
}

int linearize(int pos1, int pos2, int shape1, int shape2)
{
    return pos1 * shape2 + pos2;
}

void cpu_computer::Add1DArrays(const float *x, const float *y, float *r, size_t arrayLength)
{
    for ( unsigned long index = 0; index < arrayLength; index++ )
    {
        r[index] = x[index] + y[index];
    }
}

void cpu_computer::Multiply1DArrays(const float *x, const float *y, float *r, size_t arrayLength)
{
    for ( unsigned long index = 0; index < arrayLength; index++ )
    {
        r[index] = x[index] * y[index];
    }
}

void cpu_computer::Add2DArrays(const float* a, const float* b, float* r, size_t rows, size_t columns)
{
    for( unsigned long i = 0; i < rows; i++)
    {
        for ( unsigned long j = 0; j < columns; j++)
        {
            *(r + i * columns + j) = *(a + i * columns + j) + *(b + i * columns + j);
        }
    }
}

void cpu_computer::Multiply2DArrays(const float* a, const float* b, float* r, size_t rows, size_t columns)
{
    for (unsigned long i = 0; i < rows * columns; i++)
       {
           r[i] = 0.0f;
    }
    
    for (unsigned long i = 0; i < rows; i++)
        {
            for (unsigned long j = 0; j < columns; j++)
            {
                for (unsigned long k = 0; k < columns; k++) // Assuming square matrices
                {
                    *(r + i * columns + j) += *(a + i * columns + k) * *(b + k * columns + j);
                }
            }
        }
}
