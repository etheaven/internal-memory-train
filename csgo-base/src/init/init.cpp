#include "init.h"
#include "sdk.h"
#include "../src_headers.h"
#include <cstdio>

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
    //
    void *client = util::EasyInterface("client.dll", "VClient");
    printf("debug: 0x%p\n", client);
}