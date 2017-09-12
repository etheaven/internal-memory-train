#include "init.h"
#include "sdk.h"
#include "../src_headers.h"
#include "vmthook.h"
#include "../createmove.h"

#include <cstdio>

CClientBase *g_pClient = nullptr;
CClientMode *g_pClientMode = nullptr;
CGlobalVars *g_pGlobals = nullptr;
#ifndef __TOUCH_TIER_0__
g_pMsg = nullptr;
g_pWarning = nullptr;
#endif

VMTHook *vmt_cmove;

void SetupConsole()
{
    AllocConsole();
    //make sure I can write to it
    freopen("CONOUT$", "wb", stdout);
    freopen("CONOUT$", "wb", stderr);
    freopen("CONIN$", "rb", stdin);
    SetConsoleTitle("Debug");
}

void init::setup()
{
    SetupConsole();
//
#ifndef __TOUCH_TIER_0__
    g_pMsg = getexport<MsgFn>("tier0.dll", "Msg");
    g_pWarning = getexport<WarningFn>("tier0.dll", "Warning");
    g_pMsg("aaa\n");
#endif

    g_pClient = (CClientBase *)util::EasyInterface("client.dll", "VClient");
    printf("debug: 0x%p\n", (void *)g_pClient);
    DWORD *clienttable = (DWORD *)*(DWORD *)g_pClient;
    //\x8B\x0D????\x85\xC9\x75\x06

    g_pClientMode = **(CClientMode ***)(util::findpattern(clienttable[10], 0x100, "\x8B\x0D????\x85\xC9\x75\x06") + 0x02); //http://www.unknowncheats.me/forum/source-engine/159253-finding-pointer-clientmode-any-game.html
    printf("clientmode: 0x%p\n", (void *)g_pClientMode);
    g_pGlobals = **(CGlobalVars ***)(util::findpattern(clienttable[0], 0x100, "\xA3") + 0x01); //http://www.unknowncheats.me/forum/source-engine/160691-finding-globalvars-internally-without-having-have-any-kinda-reversing-knowledge.html
    printf("global: 0x%p\n", (void *)g_pGlobals);

    vmt_cmove = new VMTHook(g_pClientMode);
    vmt_cmove->HookFunction((void *)hkCreateMove, 24);
}