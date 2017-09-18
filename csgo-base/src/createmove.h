#pragma once
#include "src_headers.h"
#include "constants/definitions.h"
#include "math.h"

#include <cstdio>

void rcs(CUserCmd *cmd, CEntity *local)
{
	if (local->getshotsfired() <= 1)
		return;
	if (local->getactiveweapon() == 0xFFFFFFFF)
		return;
	vec3f punchAngles = (*local->getaimpunchangle()) * 2.0f;
	if (punchAngles != 0.f)
	{
		cmd->viewangles -= punchAngles;
		cmd->viewangles.clamp();
	}
}
void bhop(CUserCmd *cmd, CEntity *local)
{
	if (local->gethealth() < 1)
		return;
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

bool IsBallisticWeapon(void *weapon)
{
	if (weapon == nullptr)
		return false;
	char *pWeapon = (char *)weapon;
	int id = *(pWeapon + 0x2F88);
	return !(id >= WEAPON_KNIFE_CT && id <= WEAPON_KNIFE_T || id == 0 || id >= WEAPON_KNIFE_BAYONET);
}
void aimbot(CUserCmd *cmd, CEntity *local)
{
	float bestFov = 4.f;
	float bestRealDistance = 4.f * 5.f;
	float bestDistance = 999999999.0f;
	int bestHp = 100;
	for (int i = 0; i < g_pEngine->GetMaxClients(); ++i)
	{
		CEntity *pEntity = g_pEntityList->getcliententity(i);
		if (!pEntity || pEntity == local || pEntity->isdormant() || pEntity->gethealth() < 1)
			continue;
		if (pEntity->getteam() == local->getteam())
			continue;

		Vector vecEntityPos = pEntity->GetBonePosition(6);
		Vector vecLocalPos = local->geteyepos();

		Vector engineAngles;
		g_pEngine->GetViewAngles(engineAngles);
		void *pWeapon = g_pEntityList->entfromhandle(local->getactiveweapon());
		if (!pWeapon)
			return;
		if (!IsBallisticWeapon(pWeapon))
			return;
		
	}
}

bool __fastcall hkCreateMove(void *, void *, float, CUserCmd *cmd)
{
	if (cmd->command_number == 0) //if command_number is 0 then ExtraMouseSample is being called
		return 0;

	CEntity *local = g_pEntityList->getcliententity(g_pEngine->GetLocalPlayer());
	if (!local)
		return 0;

	bhop(cmd, local);
	rcs(cmd, local);
	aimbot(cmd, local);
	return 0;
}