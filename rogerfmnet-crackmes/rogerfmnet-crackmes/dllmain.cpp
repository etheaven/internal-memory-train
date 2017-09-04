// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"


using ulong = unsigned long;
void loop();

void setup()
{
	//00401140 - last 2 bytes
	ulong target_1 = 0x00401140;
	ulong old_protec = PAGE_EXECUTE_READ;
	VirtualProtect((void*)(target_1), 4, PAGE_EXECUTE_READWRITE, &old_protec);
	memset((void*)(target_1), 0x90, 2);
	VirtualProtect((void*)(target_1), 4, old_protec, NULL);
	//0040114A - last 2 bytes
	ulong target_2 = 0x0040114A;
	VirtualProtect((void*)(target_2), 4, PAGE_EXECUTE_READWRITE, &old_protec);
	memset((void*)(target_2), 0x90, 2);
	VirtualProtect((void*)(target_2), 4, old_protec, NULL);
	loop();
}

void loop()
{

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)setup, nullptr, NULL, nullptr);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

