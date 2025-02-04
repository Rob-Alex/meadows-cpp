# **Meadows**

A C++ implementation of a simulation library called meadows. 

---

## **Overview**

**Meadows** was originally a project that I demonstrates the use of `metal-cpp`, Apple's C++ interface to the Metal API. However extension to other platforms would also be great. Its purpose is to help me learn how to create high-performance simulations and visualize them in real-time hoping I can use this during my PhD, my plan is to document this on [my blog](https://rob-blog.co.uk). Some of the basic features are:

- A simulation pipeline for generating dynamic data.
- A rendering pipeline for visualizing the simulation results on-screen.
- Integration with Metal shaders for efficient computation and graphics.

The project showcases:

- Metal's GPU-accelerated capabilities for both compute and rendering tasks.
- A modular C++ design for handling simulation data and its visualization.

---

## **Features**

- **Simulation Framework**:
  - Uses a `Simulator` class to generate and manage dynamic simulation data.
  - Leverages Metal compute buffers for efficient data storage and updates.

- **Rendering Framework**:
  - Includes a `Renderer` class to build meshes, manage GPU buffers, and render simulation data.
  - Implements Metal's graphics pipeline for real-time visualization.
  - Metal shaders (`vertex` and `fragment`) for GPU-accelerated rendering.

- **High Performance**:
  - Takes full advantage of Metal's low-overhead API for both computation and rendering. *I am not sure if this is strictly true anymore*
  - Optimized buffer management to minimize data transfer between CPU and GPU. *WIP* 

---

## **Installation**

### **Prerequisites**

I will try update this as the project grows

1. **macOS**:
   - Meadows is designed for macOS and uses Metal, Apple's graphics API.
2. **Xcode**:
   - Install [Xcode](https://developer.apple.com/xcode/) for building the project.
3. **CMake**:
   - Ensure [CMake](https://cmake.org/) is installed to configure and build the project.
4. **metal-cpp**:
   - Meadows uses Apple's `metal-cpp`. Clone the repository or ensure `metal-cpp` is available in your project environment.

   Clone `metal-cpp` from Apple's repository:

   ```bash
   
   git clone https://github.com/apple/metal-cpp.git

---

## **TODOs**
which there are many 
- [ ] Extend render functionality to CUDA + Vulkan
    - [ ] ompute Interface
    - [ ] Renderer Interface
- [ ] Decouple render mesh from simulator mesh
    - [ ] Introduce mesh generation and interpolation layer where no assumption of the mesh connectivity is made 
    - [ ] multiple visualisation modes (vector fields, heatmaps, isosurfaces?)
    - [ ] LOD downsampling
- [ ] Fix project structure so compute, physics, and rendering are seperate

### **Physics**
- [ ] Lattice Boltzmann Method
    - [ ] D2Q9
    - [ ] D3Q1
- [ ] Finite Difference Time Domain 
    - [ ] 2D
    - [ ] 3D
