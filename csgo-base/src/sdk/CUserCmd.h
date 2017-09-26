#pragma once
#include "../vector.h"
#include "../sdk.h"
struct CUserCmd
{
	virtual ~CUserCmd() {};
	int command_number;
	int tick_count;
	vec3f viewangles;
	vec3f aimdirection;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	unsigned char impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
	vec3f headangles;
	vec3f headoffset;
};
