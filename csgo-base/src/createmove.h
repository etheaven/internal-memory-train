#pragma once
#include "src_headers.h"
#include "constants/definitions.h"

#include <cstdio>

bool __fastcall hkCreateMove(void *, void *, float, CUserCmd *cmd)
{
    if (cmd->command_number == 0) //if command_number is 0 then ExtraMouseSample is being called
        return 0;

    CEntity *local = g_pEntityList->getcliententity(g_pEngine->getlocalplayer());
    if (!local)
        return 0;
    
    if (cmd->buttons &IN_JUMP && (!(local->flags() &FL_ONGROUND)))
    {
        cmd->buttons &= ~IN_JUMP; 
    }
    return 0;
}