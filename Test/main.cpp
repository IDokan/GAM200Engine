#include <Engine.hpp>

int main()
{
    Engine engine;

    engine.Init();

    while (!engine.IsRunning())
    {
        engine.Update();
    }

    engine.Clear();

    return 0;
}