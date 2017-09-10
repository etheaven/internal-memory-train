#include <iostream>
#include <Windows.h>
using ulong = unsigned long;

void redirect_jmp(ulong dst, const byte asm_byte)
{
    *(byte *)dst = asm_byte;
}

void patch_ads()
{
    redirect_jmp(0x004091B7, 0xEB);
}

void patch_premium_reset()
{
    ulong oldprot;
    VirtualProtect((void *)0x0044FECC, 6, PAGE_EXECUTE_READWRITE, &oldprot);
    memset((void *)0x0044FECC, 0x90, 6);
    *(byte *)0x0044FECC = 1;
    VirtualProtect((void *)0x0044FECC, 6, oldprot, NULL);
}

void setup()
{
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
        ulong threadId = 0;
        CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)setup, nullptr, NULL, &threadId);
        break;
    }
    return TRUE;
}