#pragma once
#include "src_headers.h"
#include "constants/definitions.h"
#include "math.h"

#include <iostream>
#include <fstream>

static std::ofstream fout("dexdata.txt");

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

#define M_RADPI 57.295779513082f
#define M_PI 3.14159265358979323846
#define M_PI_F ((float)(M_PI))
void MakeVector( Vector angle, Vector& vector )
{
	float pitch = float( angle[ 0 ] * M_PI / 180 );
	float yaw = float( angle[ 1 ] * M_PI / 180 );
	float tmp = float( cos( pitch ) );
	vector[ 0 ] = float( -tmp * -cos( yaw ) );
	vector[ 1 ] = float( sin( yaw )*tmp );
	vector[ 2 ] = float( -sin( pitch ) );
}

float FovToPlayer(Vector ViewOffSet, Vector View, CEntity *pEntity, int bone)
{
	Vector out[9];
	const float MaxDegrees = 180.0f;
	Vector Angles = View;
	Vector Origin = ViewOffSet;
	Vector Delta(0, 0, 0);
	Vector Forward(0, 0, 0);
	AngleVectors(Angles, &Forward);
	Vector AimPos = pEntity->GetBonePosition(bone);
	Delta = AimPos - Origin; // VectorSubtract(AimPos, Origin, Delta);
	Normalize(Delta, Delta);
	//float DotProduct = Forward.Dot(Delta);
	return sqrt(Delta.x*Delta.x + Delta.y*Delta.y + Delta.z*Delta.z);/* (acosf(DotProduct) * (MaxDegrees / PI)); */
}

Vector CalcAngle( Vector Source, Vector Destination )
{
	//#pragma warning(disable : 4244)
	Vector angles;
	Vector delta;
	delta.x = (Source.x - Destination.x);
	delta.y = (Source.y - Destination.y);
	delta.z = (Source.z - Destination.z);

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
	angles.x = (float)(atanf(delta.z / hyp) * 57.295779513082f);
	angles.y = (float)(atanf(delta.y / delta.x) * 57.295779513082f);

	angles.z = 0.0f;
	if (delta.x >= 0.0) { angles.y += 180.0f; }
	return angles;
}
float Dot( const Vector &v1, Vector &v2 )
{
	return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}

float GetFov( Vector angle, Vector src, Vector dst )
{
	Vector ang, aim;
	ang = CalcAngle( src, dst);
	MakeVector( angle, aim);
	MakeVector( ang, ang);

	float mag = sqrt( pow( aim.x, 2 ) + pow( aim.y, 2 ) + pow( aim.z, 2 ) );
	float u_dot_v = Dot( aim, ang );

	return RAD2DEG( acos( u_dot_v / ( pow( mag, 2 ) ) ) );
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
	float bestFov = 12.f;
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
			return;
		if (!IsBallisticWeapon(pWeapon))
			return;
		float fov = GetFov(engineAngles, vecLocalPos, vecEntityPos);// GetFov(vecLocalPos, engineAngles, pEntity, 6);
		//printf("fov: %.2f - minfov: %.2f - pWeapon: 0x%p\n", fov, minFov, (void*)pWeapon);
		if (fov < minFov)
		{
			minFov = fov;
			target = i;
		}
	}
	printf("target: %d\n", target);
	if (target < 0)
		return;
	CEntity *pTarget = g_pEntityList->getcliententity(target);
	vecEntityPos = pTarget->GetBonePosition(6);
	Vector result = CalcAngle(vecLocalPos, vecEntityPos);
	result.clamp();
	g_pEngine->SetViewAngles(result);
	cmd->buttons |= IN_ATTACK;
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