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
        if (!setup()){
            return FALSE;
        }
        break;
    case DLL_PROCESS_DETACH:
        if (!init::detach()){
            // log xd
            return FALSE;
        }
        break;
    }
    return TRUE;
}