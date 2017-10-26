#include "init.h"
#include "../sdk.h"
#include "../src_headers.h"
#include "../vmt.h"
#include "../createmove.h"
#include "../painttraverse.h"

#include <cstdio>
#include "../util/string_constex.h"

CClientBase *g_pClient = nullptr;
IClientModeShared *g_pClientMode = nullptr;
CGlobalVars *g_pGlobals = nullptr;

IVEngineClient *g_pEngine = nullptr;
IEngineTrace *g_pEngineTrace = nullptr;

IClientEntityList *g_pEntityList = nullptr;
CGameMovement *g_pGamemovement = nullptr;

PaintTraverseFn oPaintTraverse = nullptr;
IPanel *g_pPanel = nullptr;
ISurface *g_pSurface = nullptr;
IVDebugOverlay *g_pDebugOverlay = nullptr;

IInputSystem *g_pInputSystem = nullptr;

#ifndef __TOUCH_TIER_0__
MsgFn g_Msg = nullptr;
WarningFn g_Warning = nullptr;
#endif

VMTManager VMTClientMode, VMTPaintTraverse;

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

#ifndef __TOUCH_TIER_0__
    g_Msg = util::getexport<MsgFn>("tier0.dll", "Msg");
    g_Warning = util::getexport<WarningFn>("tier0.dll", "Warning");
    g_Msg("aaa\n");
#endif

    g_pClient = (CClientBase *)util::EasyInterface(static_cast<std::string>(LIT(("client.dll"))).c_str(), static_cast<std::string>(LIT(("VClient0"))).c_str());
    printf("client: 0x%p\n", (void *)g_pClient);
    g_pEngine = (IVEngineClient *)util::EasyInterface(static_cast<std::string>(LIT(("engine.dll"))).c_str(), static_cast<std::string>(LIT(("VEngineClient0"))).c_str());
    printf("engine: 0x%p\n", (void *)g_pEngine);
    g_pEngineTrace = (IEngineTrace *)util::EasyInterface(static_cast<std::string>(LIT(("engine.dll"))).c_str(), static_cast<std::string>(LIT(("EngineTraceClient0"))).c_str());
    printf("engineTrace: 0x%p\n", (void *)g_pEngineTrace);
    g_pEntityList = (IClientEntityList *)util::EasyInterface(static_cast<std::string>(LIT(("client.dll"))).c_str(), static_cast<std::string>(LIT(("VClientEntityList0"))).c_str());
    printf("entityList: 0x%p\n", (void *)g_pEntityList);
    DWORD *clienttable = (DWORD *)*(DWORD *)g_pClient;
    g_pClientMode = **(IClientModeShared ***)((*(DWORD **)g_pClient)[10] + 0x5);
    printf("clientmode: 0x%p\n", (void *)g_pClientMode);
    g_pGlobals = **(CGlobalVars ***)((*(DWORD **)g_pClient)[0] + 0x1B);
    g_pGamemovement = (CGameMovement *)util::EasyInterface(static_cast<std::string>(LIT(("client.dll"))).c_str(), static_cast<std::string>(LIT(("GameMovement00"))).c_str());
    printf("gamemovement: 0x%p\n", (void *)g_pGamemovement);
    if (!g_pGlobals)
        g_pGlobals = **(CGlobalVars ***)(util::findpattern(clienttable[0], 0x100, "\xA3") + 0x01); //http://www.unknowncheats.me/forum/source-engine/160691-finding-globalvars-internally-without-having-have-any-kinda-reversing-knowledge.html
    printf("global: 0x%p\n", (void *)g_pGlobals);
    g_pPanel = (IPanel *)util::EasyInterface(static_cast<std::string>(LIT(("vgui2.dll"))).c_str(), static_cast<std::string>(LIT(("VGUI_Panel0"))).c_str());
    printf("panel: 0x%p\n", (void *)g_pPanel);
    g_pSurface = (ISurface *)util::EasyInterface(static_cast<std::string>(LIT(("vguimatsurface.dll"))).c_str(), static_cast<std::string>(LIT(("VGUI_Surface0"))).c_str());
    printf("surface: 0x%p\n", (void *)g_pSurface);
    
    g_pDebugOverlay = (IVDebugOverlay *)util::EasyInterface(static_cast<std::string>(LIT(("engine.dll"))).c_str(), static_cast<std::string>(LIT(("VDebugOverlay00"))).c_str());
    printf("debugoverlay: 0x%p\n", (void *)g_pDebugOverlay);
    
    g_pInputSystem = (IInputSystem *)util::EasyInterface(static_cast<std::string>(LIT(("inputsystem.dll"))).c_str(), static_cast<std::string>(LIT(("InputSystemVersion00"))).c_str());
    printf("inputSystem: 0x%p\n", (void *)g_pInputSystem);

    try {
        g_pMenu = new CMenu(); //TODO: unique ptr
    } catch(...){
        printf("Error in menu creation\n");
        return false;
    }

    try{
        VMTClientMode.Initialise((DWORD *)g_pClientMode);
        VMTClientMode.HookMethod((DWORD)hkCreateMove, 24);
    }catch(...){
        printf("VMTClientMode failure\n");
    }
    if (!VMTClientMode.getInit())
        return false;


        try{
            VMTPaintTraverse.Initialise((DWORD *)g_pPanel);
            oPaintTraverse = (PaintTraverseFn)VMTPaintTraverse.HookMethod((DWORD)&hkPaintTraverse, 41);
        }catch(...){
            printf("VMTPaintTraverse failure\n");
        }

    if (!VMTPaintTraverse.getInit())
        return false;
    return true;
}

bool init::detach()
{
    if (VMTClientMode.getInit())
        return false;
        
    if (g_pMenu)
        delete g_pMenu;

    if (VMTPaintTraverse.getInit())
        return false;
    VMTClientMode.RestoreOriginal();
    VMTPaintTraverse.RestoreOriginal();
    return true;
}