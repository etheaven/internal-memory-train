#include <Windows.h>
#include "init/init.h"

extern "C" BOOL APIENTRY DllMain(
    HMODULE,
    DWORD ul_reason_for_call,
    LPVOID)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init::setup, 0, 0, 0);
        break;
    }
    return TRUE;
}