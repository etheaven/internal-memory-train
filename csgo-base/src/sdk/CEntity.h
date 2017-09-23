#pragma once
#include <Windows.h>
#include "../sdk.h"

struct model_t;

#define MAX_SHOOT_SOUNDS 16
#define MAX_WEAPON_STRING 80
#define MAX_WEAPON_PREFIX 16
#define MAX_WEAPON_AMMO_NAME 32

enum WeaponSound_t
{
    EMPTY,
    SINGLE,
    SINGLE_NPC,
    WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
    DOUBLE_NPC,
    BURST,
    RELOAD,
    RELOAD_NPC,
    MELEE_MISS,
    MELEE_HIT,
    MELEE_HIT_WORLD,
    SPECIAL1,
    SPECIAL2,
    SPECIAL3,
    TAUNT,
    FAST_RELOAD,

    // Add new shoot sound types here
    REVERSE_THE_NEW_SOUND,

    NUM_SHOOT_SOUND_TYPES,
};

enum MoveType_t
{
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
};

enum DataUpdateType_t
{
    DATA_UPDATE_CREATED = 0,
    DATA_UPDATE_DATATABLE_CHANGED,
};

class ICollideable
{
  public:
    virtual void pad0();
    virtual const Vector &OBBMins() const;
    virtual const Vector &OBBMaxs() const;
};

class IHandleEntity
{
  public:
    virtual ~IHandleEntity(){};
};

class IClientUnknown : public IHandleEntity
{
};
class IClientRenderable
{
  public:
    virtual ~IClientRenderable(){};

    model_t *GetModel()
    {
        typedef model_t *(*oGetModel)(void *);
        return util::getvfunc<oGetModel>(this, 8)(this);
    }

    bool SetupBones(matrix3x4_t *pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0)
    {
        typedef bool (*oSetupBones)(void *, matrix3x4_t *, int, int, float);
        return util::getvfunc<oSetupBones>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
    }
};

class IClientNetworkable
{
  public:
    virtual ~IClientNetworkable(){};

    void Release()
    {
        typedef void (*oRelease)(void *);
        return util::getvfunc<oRelease>(this, 1)(this);
    }

    /* 	ClientClass* GetClientClass()
	{
		typedef ClientClass* (* oGetClientClass)(void*);
		return util::getvfunc<oGetClientClass>(this, 2)(this);
	} */

    void PreDataUpdate(DataUpdateType_t updateType)
    {
        typedef void (*oPreDataUpdate)(void *, DataUpdateType_t);
        return util::getvfunc<oPreDataUpdate>(this, 6)(this, updateType);
    }

    bool GetDormant()
    {
        typedef bool (*oGetDormant)(void *);
        return util::getvfunc<oGetDormant>(this, 9)(this);
    }

    int GetIndex()
    {
        typedef int (*oGetIndex)(void *);
        return util::getvfunc<oGetIndex>(this, 10)(this);
    }

    void SetDestroyedOnRecreateEntities()
    {
        typedef void (*oSetDestroyedOnRecreateEntities)(void *);
        return util::getvfunc<oSetDestroyedOnRecreateEntities>(this, 13)(this);
    }
};

class IClientThinkable
{
  public:
    virtual ~IClientThinkable(){};
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
  public:
    virtual ~IClientEntity(){};
};

class C_BaseEntity : public IClientEntity
{
  public:
    /*     IClientNetworkable *GetNetworkable()
    {
        return (IClientNetworkable *)((uintptr_t)this + 0x10);
    }

    void SetModelIndex(int index)
    {
        typedef void (*oSetModelIndex)(void *, int);
        return getvfunc<oSetModelIndex>(this, 111)(this, index);
    }

    int *GetModelIndex()
    {
        return (int *)((uintptr_t)this + offsets.DT_BaseViewModel.m_nModelIndex);
    }

    float GetAnimTime()
    {
        return *(float *)((uintptr_t)this + offsets.DT_BaseEntity.m_flAnimTime);
    }

    float GetSimulationTime()
    {
        return *(float *)((uintptr_t)this + offsets.DT_BaseEntity.m_flSimulationTime);
    } */

    int GetTeam()
    {
        return util::readptr<int>(this, 0xF0); //m_iTeamNum
    }

    /* 
    Vector GetVecOrigin()
    {
        return *(Vector *)((uintptr_t)this + offsets.DT_BaseEntity.m_vecOrigin);
    }

    MoveType_t GetMoveType()
    {
        return *(MoveType_t *)((uintptr_t)this + offsets.DT_BaseEntity.m_MoveType);
    }

    ICollideable *GetCollideable()
    {
        return (ICollideable *)((uintptr_t)this + offsets.DT_BaseEntity.m_Collision);
    }

    bool *GetSpotted()
    {
        return (bool *)((uintptr_t)this + offsets.DT_BaseEntity.m_bSpotted);
    } */
};

class CEntity
{
  public:
    inline BYTE lifestate()
    {
        return util::readptr<int>(this, 0x25B); //m_lifeState
    }
    inline int gethealth()
    {
        return util::readptr<int>(this, 0xFC); //m_iHealth
    }
    inline int getteam()
    {
        return util::readptr<int>(this, 0xF0); //m_iTeamNum
    }
    inline int flags()
    {
        return util::readptr<int>(this, 0x100); //m_fFlags
    }
    inline Vector *getaimpunchangle()
    {
        return util::makeptr<Vector>(this, 0x301C); //m_Local + m_aimPunchAngle
    }
    inline Vector getviewoffset()
    {
        return util::readptr<Vector>(this, 0x104); // m_vecViewOffset
    }
    inline Vector *getviewpunchangle()
    {
        return util::makeptr<Vector>(this, 0x3010); //m_Local + m_viewPunchAngle
    }
    inline int gettickbase()
    {
        return util::readptr<int>(this, 0x3404); //m_nTickBase
    }
    inline DWORD getactiveweapon()
    {
        return util::readptr<DWORD>(this, 0x2EE8); //m_hActiveWeapon
    }
    inline bool isdormant()
    {
        return util::getvfunc<bool(__thiscall *)(void *)>((this + 0x8), 9)((this + 0x8));
    }
    inline void *getmodel()
    {
        return util::getvfunc<void *(__thiscall *)(void *)>((this + 0x4), 8)((this + 0x4));
    }
    /*  inline Vector &getabsorigin()
    {
        return util::getvfunc<Vector &(__thiscall *)(void *)>(this, 10)(this);
    } */
    inline Vector getorigin()
    { // feet origin
        reutrn util::readptr < Vector < (this, 0x134);
    }
    inline Vector getabsorigin()
    {
        typedef Vector(__thiscall * GetAbsOriginFn)(void *);
        return util::getvfunc<GetAbsOriginFn>(this, 10)(this);
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
    inline Vector GetBonePosition(int Bone)
    {
        matrix3x4_t MatrixArray[128];
        if (!this->setupbones(MatrixArray, 128, 0x00000100, g_pEngine->GetLastTimeStamp()))
            return Vector(0, 0, 0);
        auto &HitboxMatrix = MatrixArray[Bone];
        return Vector(HitboxMatrix[0][3], HitboxMatrix[1][3], HitboxMatrix[2][3]);
    }
    inline bool GetBonePosition(Vector &Hitbox, int Bone)
    {
        matrix3x4_t MatrixArray[128];

        if (!this->setupbones(MatrixArray, 128, 0x00000100, g_pEngine->GetLastTimeStamp()))
            return false;

        auto &HitboxMatrix = MatrixArray[Bone];

        Hitbox = Vector(HitboxMatrix[0][3], HitboxMatrix[1][3], HitboxMatrix[2][3]);

        return true;
    }
    inline int getshotsfired()
    {
        return util::readptr<int>(this, 0xA2A0);
    }
};