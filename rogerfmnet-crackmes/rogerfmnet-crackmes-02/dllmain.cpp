// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

using ulong = unsigned long;
void loop();

void setup()
{/*
 .text:004010CB loc_4010CB:                             ; CODE XREF: DialogFunc+8Ej
 .text:004010CB                 cmp     ax, 3EBh
 .text:004010CF                 jnz     loc_401179
 .text:004010D5                 push    19h             ; cchMax
 .text:004010D7                 push    offset String   ; lpString
 .text:004010DC                 push    3E9h            ; nIDDlgItem
 .text:004010E1                 push    [ebp+hWnd]      ; hDlg
 .text:004010E4                 call    GetDlgItemTextA
 .text:004010E9                 push    19h             ; cchMax
 .text:004010EB                 push    offset byte_403015 ; lpString
 .text:004010F0                 push    3EAh            ; nIDDlgItem
 .text:004010F5                 push    [ebp+hWnd]      ; hDlg
 .text:004010F8                 call    GetDlgItemTextA
 .text:004010FD                 call    sub_40117F
 .text:00401102                 cmp     eax, 0F7C4h
 .text:00401107                 jnz     short loc_40111F
 */
 //00401107
	ulong target_1 = 0x00401107;
	ulong old_protec = PAGE_EXECUTE_READ;
	VirtualProtect((void*)(target_1), 4, PAGE_EXECUTE_READWRITE, &old_protec);
	memset((void*)(target_1), 0x90, 2);
	VirtualProtect((void*)(target_1), 4, old_protec, NULL);
	loop();
}

void loop()
{

}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch(ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)setup, nullptr, NULL, nullptr);
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

