#include <Windows.h>
#include <cstdio>
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
        try{
            if (!init::setup()){
                printf("failed to attach\n");
                return FALSE;
            }
        }catch(...){
            printf("failed in fail of attach\n");
            return FALSE;
        }
        break;
    case DLL_PROCESS_DETACH:
        try{
            if (!init::detach()){
                // log xd
                printf("failed to detach\n");
                return FALSE;
            }
        }catch(...){
            printf("failed in fail of dettach\n");
        }
        break;
    }
    return TRUE;
}