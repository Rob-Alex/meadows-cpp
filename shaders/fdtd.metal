#include <metal_stdlib>
using namespace metal;

kernel void applyPulse(device float* electricFieldBuffer [[buffer(0)]],
                        device float* magneticFieldBuffer [[buffer(1)]],
                        constant float3& pos [[buffer(2)]], 
                        constant float& timeStep [[buffer(3)]],
                        constant float& timeDelta [[buffer(4)]],  
                        uint2 gid [[thread_position_in_grid]],
                        uint2 gridSize [[thread_per_grid]]) 
{
    //TODO:
}



