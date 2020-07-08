#include <Window/Engine.hpp>
#include <string>
#include  <Windows.h>

int main()
{
    FreeConsole();

    Engine engine;

    try {
        engine.Init();
        while (engine.GetIsRunnig() == true)
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
