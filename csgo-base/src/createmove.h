#pragma once
#include "src_headers.h"
#include "constants/definitions.h"

void rcs(CUserCmd *cmd, CEntity *local)
{
	if (local->getactiveweapon() != 0xFFFFFFFF) //do NOT read if the handle is invalid
	{
		Vector oldpunch = *local->getaimpunchangle(); //read & backup punch

		g_pGamemovement->decaypunchangle(); //decaypunchangle

		Vector newpunch = *local->getaimpunchangle(); //read new punch

		if (cmd->buttons & IN_ATTACK)
		{
			cmd->viewangles -= newpunch * 2.0f; //2.0f is magnitude https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/game/shared/gamemovement.cpp#L1229 this game runs on 2007, but same concept.
		}
		newpunch = oldpunch; //restore punch
	}
}

void bhop(CUserCmd *cmd, CEntity *local)
{
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
}

bool __fastcall hkCreateMove(void *, void *, float, CUserCmd *cmd)
{
	if (cmd->command_number == 0) //if command_number is 0 then ExtraMouseSample is being called
		return 0;

	CEntity *local = g_pEntityList->getcliententity(g_pEngine->getlocalplayer());
	if (!local)
		return 0;
	
	bhop(cmd, local);
	//rcs(cmd, local);
	return 0;
}