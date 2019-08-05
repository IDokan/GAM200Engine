/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Timer.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Header file for  delta time
******************************************************************************/
#pragma once
#include <chrono>

class Timer
{
private:
    //  Type aliases to make accessing nested type easier
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration <double, std::ratio<1>>;

    std::chrono::time_point <clock_t> timeStamp;

public:
    Timer() : timeStamp(clock_t::now())
    {};

    void Reset() noexcept
    {
        timeStamp = clock_t::now();
    }

    double GetElapsedSeconds() const noexcept
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - timeStamp).count();
    }
};