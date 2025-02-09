//
//  cpu_computer.hpp
//  Computer
//
//  Created by Robbie Alexander on 31/01/2024.
//

#ifndef cpu_computer_hpp
#define cpu_computer_hpp

#include <stdio.h>

class cpu_computer
{
public:
    cpu_computer();
    ~cpu_computer();
    void Add1DArrays(const float*, const float*, float*, size_t);
    void Multiply1DArrays(const float*, const float*, float*, size_t);
    void Add2DArrays(const float*,const float*, float*, size_t, size_t);
    void Multiply2DArrays(const float*, const float*, float*, size_t, size_t);
    
private:

};

#endif /* cpu_computer_hpp */
