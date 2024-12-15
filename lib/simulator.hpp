#ifndef simulator_hpp
#define simulator_hpp

#include "config.hpp"

class Simulator { 
    public: 
        Simulator(MTL::Device* pDevice, size_t, size_t);
        ~Simulator();
        void updateSimulation();
        MTL::Buffer* getSimulationBuffer() const; 
        size_t getGridWidth() const { return _gridWidth; }
        size_t getGridHeight() const { return _gridHeight; }

    private: 
        MTL::Device* _pDevice;
        MTL::Buffer* _pSimulationBuffer;
        size_t _gridWidth;
        size_t _gridHeight;
};

#endif 