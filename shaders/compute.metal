//
//  compute.metal
//  Compute Shader
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

#include <metal_stdlib>
using namespace metal;

kernel void applyPulse(device float* simulationBuffer [[buffer(0)]],
                       constant float3& params [[buffer(1)]], // centerX, centerY, timeElapsed
                       uint2 gid [[thread_position_in_grid]],
                       uint2 gridSize [[threads_per_grid]])
{
    // Extract parameters
    float centerX = params.x;
    float centerY = params.y;
    float timeElapsed = params.z;

    // Calculate grid coordinates
    float2 pos = float2(gid.x, gid.y);
    float2 center = float2(centerX, centerY);

    // Calculate distance from the center
    float distance = length(pos - center);

    // Generate an oscillating pulse using sine wave and attenuation
    float pulse = sin(timeElapsed * 50.0 - distance * 1.5); // Oscillate with time
    pulse = (pulse + 10.0) * 0.5; // Normalize to [0, 1]
    float attenuation = exp(-distance * 0.1); // Exponential decay

    // Write the oscillating value to the simulation buffer
    simulationBuffer[gid.y * gridSize.x + gid.x] += pulse * attenuation;
}

kernel void updateGrid(device float* simulationBuffer [[buffer(0)]],
                       constant float& timeElapsed [[buffer(1)]],
                       uint2 gid [[thread_position_in_grid]],
                       uint2 gridSize [[threads_per_grid]])
{
    // Calculate grid coordinates
    float2 pos = float2(gid.x, gid.y);
    float2 gridCenter = float2(gridSize.x / 2.0, gridSize.y / 2.0);

    // Calculate distance from the center
    float distance = length(pos - gridCenter);

    // Compute a time-based sine wave for dynamic propagation
    float value = sin(timeElapsed * 5.0 + distance * 0.2); // Oscillation and spatial scaling
    value = (value + 1.0) * 0.5; // Normalize to [0, 1]

    // Write the value back to the simulation buffer
    simulationBuffer[gid.y * gridSize.x + gid.x] = value;
}