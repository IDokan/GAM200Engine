#include <Window/Engine.hpp>
#include <string>
#include  <Windows.h>

int main()
{
    Engine engine;

    try {
        engine.Init();
        while (!engine.GetIsRunnig())
        {
            engine.Update();
        }
    }
    catch (const char * message)
    {
        MessageBoxA(NULL,message, "Error!", MB_ICONERROR);
    }
    engine.Clear();

    return 0;
}
