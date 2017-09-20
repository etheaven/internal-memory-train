#pragma once
#include "src_headers.h"
#include "constants/definitions.h"
#include "math.h"


#include <Windows.h>
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


void VectorAngles(Vector forward, Vector &angles)
{
	float tmp, yaw, pitch;

	if (forward[2] == 0 && forward[0] == 0)
	{
		yaw = 0;

		if (forward[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / PI);

		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / PI);

		if (pitch < 0)
			pitch += 360;
	}

	if (pitch > 180)
		pitch -= 360;
	else if (pitch < -180)
		pitch += 360;

	if (yaw > 180)
		yaw -= 360;
	else if (yaw < -180)
		yaw += 360;

	if (pitch > 89)
		pitch = 89;
	else if (pitch < -89)
		pitch = -89;

	if (yaw > 180)
		yaw = 180;
	else if (yaw < -180)
		yaw = -180;

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

Vector aCalcAngle(Vector src, Vector dst)
{
	Vector angles;
	auto delta = src - dst;
	VectorAngles(delta, angles);
	delta.clamp();
	return angles;
}

float aGetFov(const Vector& viewAngle, const Vector& aimAngle)
{
	auto delta = aimAngle - viewAngle;
	delta.clamp();
	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

int FovGetPlayer(CUserCmd *cmd, CEntity *local){
	float bestFov = 30.f;
	float minFov = bestFov;
	int target = -1;
	Vector vecLocalPos = local->geteyepos();
	Vector vecEntityPos = local->GetBonePosition(6);
	for (int i = 0; i < g_pEngine->GetMaxClients(); ++i)
	{
		CEntity *pEntity = g_pEntityList->getcliententity(i);
		if (!pEntity)
			continue;
		if (pEntity == local || pEntity->isdormant() || pEntity->gethealth() < 1)
			continue;
		if (pEntity->getteam() == local->getteam())
			continue;

		vecEntityPos = pEntity->GetBonePosition(6);
		vecLocalPos = local->geteyepos();

		Vector engineAngles;
		g_pEngine->GetViewAngles(engineAngles); //engineAngles += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;
		void *pWeapon = g_pEntityList->entfromhandle(local->getactiveweapon());
		if (!pWeapon)
			return target;
		if (!IsBallisticWeapon(pWeapon))
			return target;
		
		float fov = aGetFov(engineAngles, aCalcAngle(vecLocalPos, vecEntityPos));//GetFov(engineAngles, vecLocalPos, vecEntityPos);
		if (fov < minFov)
		{
			minFov = fov;
			target = i;
		}
	}
	return target;
}

int HpGetPlayer(CUserCmd *cmd, CEntity *local)
{
	int target = -1;
	int bestHp = 100;
	for(int i = 0; i < g_pEngine->GetMaxClients(); ++i){
		CEntity *pEntity = g_pEntityList->getcliententity(i);
		if (!pEntity)
			continue;
		if (pEntity == local || pEntity->isdormant() || pEntity->gethealth() < 1)
			continue;
		if (pEntity->getteam() == local->getteam())
			continue;
		if (pEntity->gethealth() < bestHp){
			bestHp = pEntity->gethealth();
			target = i;
		}
	}
	return target;
}

void aimbot(CUserCmd *cmd, CEntity *local)
{
	int target = HpGetPlayer(cmd, local);
	if (target <= 0)
		return;
	CEntity *pTarget = g_pEntityList->getcliententity(target);
	Vector vecLocalPos = local->geteyepos();
	Vector vecEntityPos = pTarget->GetBonePosition(6);
	Vector result = CalcAngle(vecLocalPos, vecEntityPos);
	result.clamp();
	g_pEngine->SetViewAngles(result);
}

bool __fastcall hkCreateMove(void *, void *, float, CUserCmd *cmd)
{
	if (cmd->command_number == 0) //if command_number is 0 then ExtraMouseSample is being called
		return 0;

	CEntity *local = g_pEntityList->getcliententity(g_pEngine->GetLocalPlayer());
	if (!local)
		return 0;

	bhop(cmd, local);
	//rcs(cmd, local);
	aimbot(cmd, local);
	return 0;
}