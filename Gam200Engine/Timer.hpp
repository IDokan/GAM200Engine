#pragma once
#include <chrono>

/*
    Should add header comment.
*/

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