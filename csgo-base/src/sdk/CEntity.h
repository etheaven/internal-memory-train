#pragma once
#include <Windows.h>
#include "../sdk.h"

class CEntity
{
  public:
    inline BYTE lifestate()
    {
        return util::readptr<int>(this, 0x25B); //m_lifeState
    }
    inline int flags()
    {
        return util::readptr<int>(this, 0x100); //m_fFlags
    }
    inline Vector *getaimpunchangle()
    {
        return util::makeptr<Vector>(this, 0x2FF8); //m_Local + m_aimPunchAngle
    }
    inline Vector *getviewpunchangle()
    {
        return util::makeptr<Vector>(this, 0x2FEC); //m_Local + m_viewPunchAngle
    }
    inline int gettickbase()
    {
        return util::readptr<int>(this, 0x33EC); //m_nTickBase
    }
    inline DWORD getactiveweapon()
    {
        return util::readptr<DWORD>(this, 0x2EC8); //m_hActiveWeapon
    }
    inline bool isdormant()
    {
        return util::getvfunc<bool(__thiscall *)(void *)>((this + 0x8), 9)((this + 0x8));
    }
    inline void *getmodel()
    {
        return util::getvfunc<void *(__thiscall *)(void *)>((this + 0x4), 8)((this + 0x4));
    }
    inline Vector &getabsorigin()
    {
        return util::getvfunc<Vector &(__thiscall *)(void *)>(this, 10)(this);
    }
    inline Vector getvecviewoffset()
    {
        return util::readptr<Vector>(this, 0x104); //m_vecViewOffset[0]
    }
    inline Vector geteyepos()
    {
        return getabsorigin() + getvecviewoffset();
    }
    inline bool setupbones(matrix3x4_t *bonematrix, int maxbones, int mask, float curtime = 0)
    {
        void *renderable = reinterpret_cast<void *>(reinterpret_cast<DWORD>(this) + 0x4);
        return util::getvfunc<bool(__thiscall *)(void *, matrix3x4_t *, int, int, float)>(renderable, 13)(renderable, bonematrix, maxbones, mask, curtime);
    }
};