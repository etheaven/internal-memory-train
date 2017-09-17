#pragma once
#include "../sdk.h"

class CBaseHandle;

class IClientEntityList
{
  public:
    inline CEntity *getcliententity(int i)
    {
        return util::getvfunc<CEntity *(__thiscall *)(void *, int)>(this, 3)(this, i);
    }
    inline CEntity *entfromhandle(unsigned int i) // DWORD
    {
        return util::getvfunc<CEntity *(__thiscall *)(void *, int)>(this, 4)(this, i);
    }
    inline int gethighestentityindex(void) // DWORD
    {
        return util::getvfunc<int(__thiscall *)(void *)>(this, 6)(this);
    }
};

extern IClientEntityList *g_pEntityList;