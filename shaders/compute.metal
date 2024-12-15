//
//  compute.metal
//  Computer
//
//  Created by Robbie Alexander on 23/01/2024.
//

#include <metal_stdlib>
using namespace metal;

kernel
void add_1D_arrays(device const float* A    [[buffer(0)]],
                   device const float* B    [[buffer(1)]],
                   device float* result     [[buffer(2)]],
                   uint index [[thread_position_in_grid]])
{
    result[index] = A[index] + B[index];
}

kernel
void multiply_1D_arrays(device const float* A    [[buffer(0)]],
                        device const float* B    [[buffer(1)]],
                        device float* result     [[buffer(2)]],
                        uint index [[thread_position_in_grid]])
{
    result[index] = A[index] * B[index];
}

int linearize(int pos1, int pos2, int shape1, int shape2)
{
    return pos1 * shape2 + pos2;
}

kernel
void add_2D_arrays(device const float* A    [[buffer(0)]],
                    device const float* B    [[buffer(1)]],
                    device float* result     [[buffer(2)]],
                    uint2 index [[thread_position_in_grid]],
                    uint2 grid  [[threads_per_grid]])
{
    int idx = linearize(index.x, index.y, grid.x, grid.y);
    result[idx] = A[idx] + B[idx];
}

kernel
void multiply_2D_arrays(device const float* A    [[buffer(0)]],
                        device const float* B    [[buffer(1)]],
                        device float* result     [[buffer(2)]],
                        uint2 index [[thread_position_in_grid]],
                        uint2 grid  [[threads_per_grid]])
{
    const uint N = grid.x; // Assuming grid size matches matrix dimensions
    // Ensure index is within bounds
    if (index.x >= N || index.y >= N) return;
    
    float sum = 0.0;
    for(uint k = 0; k < N; ++k) {
        sum += A[index.y * N + k] * B[k * N + index.x];
    }
    
    result[index.y * N + index.x] = sum;
}


