#pragma once
#include "../sdk.h"
#include "../constants/bspflags.h"
// TODO: tidy
// Trace stuff start

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

struct cplane_t
{
	Vector normal;
	float dist;
	BYTE type;
	BYTE signbits;
	BYTE pad[2];
};

class CBaseTrace
{
  public:
	Vector startpos;
	Vector endpos;
	cplane_t plane;
	float fraction;
	int contents;
	unsigned short dispFlags;
	bool allsolid;
	bool startsolid;
};

struct csurface_t
{
	const char *name;
	short surfaceProps;
	unsigned short flags;
};

class CEntity;

struct Ray_t
{
	Vector m_Start;
	Vector m_Delta;
	Vector m_StartOffset;
	Vector m_Extents;

	const matrix3x4_t *m_pWorldAxisTransform;

	bool m_IsRay; // i veri buy dem nigga
	bool m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(NULL) {}

	void Init(Vector &vecStart, Vector &vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.Length() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		m_pWorldAxisTransform = NULL;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}
};

class ITraceFilter
{
  public:
	virtual bool ShouldHitEntity(CEntity *pEntity, int contentsMask) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
  public:
	bool ShouldHitEntity(CEntity *pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void *pSkip;
};

class CGameTrace : public CBaseTrace
{
  public:
	bool DidHitWorld() const;
	bool DidHitNonWorldEntity() const;
	int GetEntityIndex() const;
	bool DidHit() const;

  public:
	float fractionleftsolid;
	csurface_t surface;
	int hitgroup;
	short physicsbone;
	unsigned short worldSurfaceIndex;
	CEntity *m_pEnt;
	int hitbox;
	char shit[0x24];
};

using trace_t = CGameTrace;

class IEngineTrace
{
  public:
	int GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, CEntity **ppEntity = NULL)
	{
		typedef int(__thiscall * fnGetPointContents)(void *, const Vector &, int, CEntity **);
		return util::getvfunc<fnGetPointContents>(this, 0)(this, vecAbsPosition, contentsMask, ppEntity);
	}

	void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void(__thiscall * oTraceRay)(PVOID, const Ray_t &, unsigned int, ITraceFilter *, trace_t *);
		return util::getvfunc<oTraceRay>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
	/* 
	void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
	{
		typedef void(__thiscall* fnTraceRay)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		util::getvfunc<fnTraceRay>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	} */
	void EdgeTraceRay(Ray_t &ray, CTraceFilter &filt, CGameTrace &trace, bool wall = false)
	{
		typedef void(__thiscall * OrigFn)(void *, Ray_t &, unsigned int, CTraceFilter &, CGameTrace &);
		return util::getvfunc<OrigFn>(this, 5)(this, ray, wall ? 0x200400B : 0x46004003, filt, trace); // 0x46004003 0x4600400B
	}
};

inline bool CGameTrace::DidHit() const
{
	return fraction < 1.0f || allsolid || startsolid;
}

extern IEngineTrace *g_pEngineTrace;