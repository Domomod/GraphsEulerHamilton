#pragma once
#include <iostream>
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
    
    void StartTimer()
    {
        start = high_resolution_clock::now();
    }
    
    
    void EndTimer()
    {
        end = high_resolution_clock::now();
    }
    
    
    long long GetDelta()
    {
        long delta = (long)duration_cast<microseconds>(end - start).count();
        
        return delta;
        //outcome << "Algorithm took " << delta << " us\n";
    }
    
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
};
