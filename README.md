# **Meadows**

A C++ implementation of a simulation and rendering pipeline using Apple's `metal-cpp` framework.

---

## **Overview**

**Meadows** is a project that demonstrates the use of `metal-cpp`, Apple's C++ interface to the Metal API, to create high-performance simulations and visualize them in real-time. It includes:

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
  - Takes full advantage of Metal's low-overhead API for both computation and rendering.
  - Optimized buffer management to minimize data transfer between CPU and GPU.

---

## **Installation**

### **Prerequisites**

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
