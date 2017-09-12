#pragma once
#include "sdk/CClientBase.h"
#include "sdk/CClientMode.h"
#include "sdk/CGlobalVars.h"
#include "sdk/CUserCmd.h"
#include "vector.h"

#define __TOUCH_TIER_0__ false

typedef void(__cdecl *MsgFn)(const char *, ...);
typedef void(__cdecl *WarningFn)(const char *, ...);

#ifndef __TOUCH_TIER_0__
extern MsgFn g_pMsg;
extern WarningFn g_pWarning;
#endif