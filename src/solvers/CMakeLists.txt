add_library(solvers 
    #MaxwellSolver.cpp
    LBMSolver.cpp
    FDTDSolver.cpp
)

target_include_directories(solvers PUBLIC ${CMAKE_SOURCE_DIR}/include/solvers)

