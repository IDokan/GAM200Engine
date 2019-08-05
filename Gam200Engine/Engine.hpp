#pragma once
#include "Timer.hpp"

class Application;

class Engine
{
private:
    bool isRunning = false;
    float dt;
    Timer timer;
public:
    Engine() = default;
    
    void Init();
    void Update();
    void Clear();

    bool IsRunning() noexcept
    {
        return isRunning;
    }
};