#include "Engine.hpp"

int main()
{
    Engine engine;

    engine.Init();

    while (!engine.GetIsRunnig())
    {
        engine.Update();
    }

    engine.Clear();

    return 0;
}