#include <Windows.h>
#include "init/init.h"

extern "C" BOOL APIENTRY DllMain(
    HMODULE boi,
    DWORD ul_reason_for_call,
    LPVOID)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(boi);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init::setup, 0, 0, 0);
        break;
    case DLL_PROCESS_DETACH:
        init::detach();
        FreeLibraryAndExitThread(boi, 0);
    }
    return TRUE;
}