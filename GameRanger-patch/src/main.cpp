#include <iostream>
#include <Windows.h>
using ulong = unsigned long;

void redirect_jmp(ulong dst)
{
    ulong oldprot;
    VirtualProtect((void *)dst, 2, PAGE_EXECUTE_READWRITE, &oldprot);
    memset((void *)dst, 0x90, 2);
    *(byte *)dst = 0xEB;
    *(byte *)(dst + 1) = 0x1F;
    VirtualProtect((void *)dst, 2, oldprot, NULL);
}

void patch_ads()
{
    redirect_jmp(0x004091B7);
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
    patch_ads();
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