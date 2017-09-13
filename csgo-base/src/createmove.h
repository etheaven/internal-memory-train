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
    
        static bool bLastJumped = false;
		static bool bShouldFake = false;
 
		if (!bLastJumped && bShouldFake)
		{
			bShouldFake = false;
			cmd->buttons |= IN_JUMP;
		}
		else if (cmd->buttons & IN_JUMP)
		{
			if (local->flags() & FL_ONGROUND)
			{
				bLastJumped = true;
				bShouldFake = true;
			}
			else
			{
				cmd->buttons &= ~IN_JUMP;
				bLastJumped = false;
			}
		}
		else
		{
			bLastJumped = false;
			bShouldFake = false;
		}
    return 0;
}