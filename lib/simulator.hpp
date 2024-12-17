#ifndef simulator_hpp
#define simulator_hpp

#include "config.hpp"
#include <map>
#include <list>
#include <vector>


/// @brief Simulator class
class Simulator { 
    public: 
        Simulator(MTL::Device* pDevice, size_t, size_t);
        ~Simulator();

        void loadComputeShaders(const std::string& shaderPath);
        void updateSimulation(float);
        void applyPulse(float, float, float);
        void dispatchCompute2D(const char*, MTL::Buffer*, void*, size_t);
        MTL::Buffer* getSimulationBuffer() const { return _pSimulationBuffer; } 
        size_t getGridWidth() const { return _gridWidth; }
        size_t getGridHeight() const { return _gridHeight; }

    private: 
        // metal device 
        MTL::Device* _pDevice;
        MTL::CommandQueue* _pCmdQ;
        std::map<std::string, MTL::ComputePipelineState*> _pComputePipelines;

        //simulation data
        MTL::Buffer* _pSimulationBuffer;
        size_t _gridWidth;
        size_t _gridHeight;
};

//simulator interface for solvers
class ISimulator { 
    public: 
        virtual ~ISimulator() = default;
        virtual void initalise() = 0;  
        virtual void update(float timestep) = 0;
        virtual MTL::Buffer* getSimulationBuffer() const = 0;
        virtual size_t getGridWidth() const = 0;
        virtual size_t getGridHeight() const = 0;
};

//finite difference time domain solver
class FDTDSolver : public ISimulator 
{

};

#endif 