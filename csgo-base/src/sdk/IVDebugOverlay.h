#pragma once
#include "../vector.h"
#include "../src_headers.h"
class IVDebugOverlay
{
public:
  int ScreenPosition(const Vector &in, Vector &out)
  {
    typedef int(__thiscall * OrigFn)(void *, const Vector &, Vector &);
    return util::getvfunc<OrigFn>(this, 13)(this, in, out);
  }
};
extern IVDebugOverlay *g_pDebugOverlay;