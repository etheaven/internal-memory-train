#pragma once
#include "vector.h"
#include "sdk.h"
bool W2S(const Vector &v3D, Vector &v2D)
{
    return (g_pDebugOverlay->ScreenPosition(v3D, v2D) != 1);
}

void CalcAngle(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D(); //delta.Length
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles.x = (atan(delta.z / hyp) * 57.295779513082f);
	angles.z = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}