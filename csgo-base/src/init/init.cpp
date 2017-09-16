#include "init.h"
#include "../sdk.h"
#include "../src_headers.h"
#include "../vmt.h"
#include "../createmove.h"

#include <cstdio>

CClientBase *g_pClient = nullptr;
IClientModeShared *g_pClientMode = nullptr;
CGlobalVars *g_pGlobals = nullptr;
IVEngineClient *g_pEngine = nullptr;
IClientEntityList *g_pEntityList = nullptr;
CGameMovement *g_pGamemovement = nullptr;
#ifndef __TOUCH_TIER_0__
MsgFn g_Msg = nullptr;
WarningFn g_Warning = nullptr;
#endif

VMTManager VMTClientMode;

void SetupConsole()
{
    AllocConsole();
    //make sure I can write to it
    freopen("CONOUT$", "wb", stdout);
    freopen("CONOUT$", "wb", stderr);
    freopen("CONIN$", "rb", stdin);
    SetConsoleTitle("Debug");
}

bool init::setup()
{
    SetupConsole();
//
#ifndef __TOUCH_TIER_0__
    g_Msg = util::getexport<MsgFn>("tier0.dll", "Msg");
    g_Warning = util::getexport<WarningFn>("tier0.dll", "Warning");
    g_Msg("aaa\n");
#endif

    g_pClient = (CClientBase *)util::EasyInterface("client.dll", "VClient0");
    printf("client: 0x%p\n", (void *)g_pClient);
    g_pEngine = (IVEngineClient *)util::EasyInterface("engine.dll", "VEngineClient0");
    printf("engine: 0x%p\n", (void *)g_pEngine);
    g_pEntityList = (IClientEntityList *)util::EasyInterface("client.dll", "VClientEntityList0");
    printf("entityList: 0x%p\n", (void *)g_pEntityList);
    DWORD *clienttable = (DWORD *)*(DWORD *)g_pClient;
    g_pClientMode = **(IClientModeShared ***)((*(DWORD **)g_pClient)[10] + 0x5);
    printf("clientmode: 0x%p\n", (void *)g_pClientMode);
    g_pGlobals = **(CGlobalVars ***)((*(DWORD **)g_pClient)[0] + 0x1B);
    g_pGamemovement = (CGameMovement *)util::EasyInterface("client.dll", "GameMovement00");
    printf("gamemovement: 0x%p\n", (void *)g_pGamemovement);
    if (!g_pGlobals)
        g_pGlobals = **(CGlobalVars ***)(util::findpattern(clienttable[0], 0x100, "\xA3") + 0x01); //http://www.unknowncheats.me/forum/source-engine/160691-finding-globalvars-internally-without-having-have-any-kinda-reversing-knowledge.html
    printf("global: 0x%p\n", (void *)g_pGlobals);

    VMTClientMode.Initialise((DWORD *)g_pClientMode);
    VMTClientMode.HookMethod((DWORD)hkCreateMove, 24);
    if (!VMTClientMode.getInit())
        return false;
    return true;
}

bool init::detach()
{
    VMTClientMode.RestoreOriginal();
    if (VMTClientMode.getInit())
        return false;
    return true;
}