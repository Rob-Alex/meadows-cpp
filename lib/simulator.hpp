#ifndef simulator_hpp
#define simulator_hpp

#include "config.hpp"
#include "mtl_computer.hpp"
#include <map>
/// @brief Simulator class 
// deprecated -----------------------------------------------------------------------//
class Simulator {                                                                    
    public:                         
        Simulator(MTL::Device* pDevice, size_t, size_t);
        ~Simulator();

        void updateSimulation(float);
        void applyPulse(float, float, float);

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

        mtl_computer _gpuComputer;
};
// deprecated -----------------------------------------------------------------------

// Abstract object simulator interface for solvers
class ISimulator { 
    public: 
        virtual ~ISimulator() = default;
        virtual void initialize() = 0;  
        virtual void update(float timestep) = 0;
        virtual void reset() = 0;
        virtual MTL::Buffer* getSimulationBuffer() const = 0;
        virtual size_t getGridWidth() const = 0;
        virtual size_t getGridHeight() const = 0;
        virtual MTL::CommandQueue* getCommandQueue() const = 0; 
};

//create test simulator for testing 
class TestSimulator : public ISimulator 
{
    public:
        TestSimulator(MTL::Device* pDevice, size_t, size_t);
        ~TestSimulator();

        void initialize() override; 
        void update(float timeStep) override; 
        void reset() override;

        MTL::Buffer* getSimulationBuffer() const override;

        size_t getGridWidth() const override { return _gridWidth; } 
        size_t getGridHeight() const override { return _gridHeight; }

        MTL::CommandQueue* getCommandQueue() const override { return _pCmdQ; }
    private: 
        void loadComputePipelines();
        
        size_t _gridWidth, _gridHeight;
        MTL::Device* _pDevice;
        MTL::CommandQueue* _pCmdQ;

        // this is the simulation data
        // could be _pElectricFieldBuffer or pTemperatureFieldBuffer for example 
        MTL::Buffer* _pSimulationBuffer;

        mtl_computer _gpuComputer;
};

class FDTDSolver : public ISimulator 
{
    public:
        FDTDSolver(MTL::Device* pDevice, size_t, size_t);
        ~FDTDSolver();

        void initialize() override; 
        void update(float timeStep) override; 
        void reset() override;

        MTL::Buffer* getElectricFieldBuffer() const; 
        MTL::Buffer* getMagneticFieldBuffer() const; 

        size_t getGridWidth() const override { return _gridWidth; }
        size_t getGridHeight() const override { return _gridHeight; }

        MTL::CommandQueue* getCommandQueue() const override { return _pCmdQ; }

    private:
        void loadComputePipelines();

        size_t _gridWidth, _gridHeight;
        MTL::Device* _pDevice;
        MTL::CommandQueue* _pCmdQ;

        MTL::Buffer* _pElectricFieldBuffer;
        MTL::Buffer* _pMagneticFieldBuffer; 

        mtl_computer _gpuComputer;
};

class MaxwellSolver : public ISimulator
{
    public:
        MaxwellSolver(MTL::Device* pDevice, size_t, size_t);
        ~MaxwellSolver();

        void initialize() override; 
        void update(float timeStep) override; 
        void reset() override;

        MTL::Buffer* getElectricFieldBuffer() const; 
        MTL::Buffer* getMagneticFieldBuffer() const; 

        size_t getGridWidth() const override { return _gridWidth; }
        size_t getGridHeight() const override { return _gridHeight; }

        MTL::CommandQueue* getCommandQueue() const override { return _pCmdQ; }   

    private:
        void loadComputePipelines();

        size_t _gridWidth, _gridHeight;
        MTL::Device* _pDevice;
        MTL::CommandQueue* _pCmdQ;

        MTL::Buffer* _pChargeDensityFieldBuffer;
        MTL::Buffer* _pFieldBuffer; 

        mtl_computer _gpuComputer;
};

#endif 
