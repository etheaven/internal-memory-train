#pragma once
#include "../src_headers.h"
class CGameMovement
{
public:
	inline void decaypunchangle()
	{
		return util::getvfunc<void(__thiscall *)(void *)>(this, 19)(this);
	}
};
extern CGameMovement *g_pGamemovement;