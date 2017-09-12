#include <iostream>
#include <Windows.h>
using ulong = unsigned long;

void get_gold_flag()
{
    ulong gold_bool = 0x005BE8F9;
    *(byte *)gold_bool = 1;
}

void patch_premium_reset()
{
    ulong oldprot;
    VirtualProtect((void *)0x0044FECC, 6, PAGE_EXECUTE_READWRITE, &oldprot);
    memset((void *)0x0044FECC, 0x90, 6);
    VirtualProtect((void *)0x0044FECC, 6, oldprot, NULL);
    // set premium flag
    ulong premium_bool = 0x005BE8F8;
    *(byte *)premium_bool = 1;
}

void setup()
{
    // TODO: anticheat? closes connection to gameranger after disabling ads is checked
    // get_gold_flag();
    patch_premium_reset();
}

extern "C" BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        setup();
        break;
    }
    return TRUE;
}