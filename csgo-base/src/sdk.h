#pragma once
#undef Vector
#include "sdk/CClientBase.h"
#include "sdk/IClientModeShared.h"
#include "sdk/CGlobalVars.h"
#include "sdk/CUserCmd.h"
#include "sdk/IVEngineClient.h"
#include "sdk/CEntity.h"
#include "sdk/IClientEntityList.h"

#include "vector.h"

//#define __TOUCH_TIER_0__ false

typedef void(__cdecl *MsgFn)(const char *, ...);
typedef void(__cdecl *WarningFn)(const char *, ...);

#ifndef __TOUCH_TIER_0__
extern MsgFn g_Msg;
extern WarningFn g_Warning;
#endif