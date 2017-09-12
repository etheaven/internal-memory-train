#pragma once
#include "sdk.h"
using ulong = unsigned long;
extern bool __fastcall CreateMove(void*, void*, float, CUserCmd*);
typedef void (*CreateMove_t) (void*, void*, float, CUserCmd*);
/* extern void __fastcall painttraverse(void*, void*, unsigned int, bool, bool);
extern void __fastcall framestagenotify(void*, void*, clientframestage_t);
typedef void(__thiscall *painttraverse_t)(void*, unsigned int, bool, bool);
typedef void(__thiscall *framestagenotify_t)(void*, clientframestage_t);
extern framestagenotify_t org_framestagenotify; */