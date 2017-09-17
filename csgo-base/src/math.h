#pragma once
#include "vector.h"
#include "sdk.h"
bool W2S(const Vector &v3D, Vector &v2D)
{
    return (g_pDebugOverlay->ScreenPosition(v3D, v2D) != 1);
}

static bool screen_transform(const Vector &in, Vector &out)
{
    static auto &w2sMatrix = g_pEngine->WorldToScreenMatrix();

    out.x = w2sMatrix[0][0] * in.x + w2sMatrix[0][1] * in.y + w2sMatrix[0][2] * in.z + w2sMatrix[0][3];
    out.y = w2sMatrix[1][0] * in.x + w2sMatrix[1][1] * in.y + w2sMatrix[1][2] * in.z + w2sMatrix[1][3];
    out.z = 0.0f;

    float w = w2sMatrix[3][0] * in.x + w2sMatrix[3][1] * in.y + w2sMatrix[3][2] * in.z + w2sMatrix[3][3];

    if (w < 0.001f)
    {
        out.x *= 100000;
        out.y *= 100000;
        return false;
    }

    out.x /= w;
    out.y /= w;

    return true;
}
bool WorldToScreen(const Vector &in, Vector &out)
{
    if (screen_transform(in, out))
    {
        int w, h;
        g_pEngine->GetScreenSize(w, h);

        out.x = (w / 2.0f) + (out.x * w) / 2.0f;
        out.y = (h / 2.0f) - (out.y * h) / 2.0f;

        return true;
    }
    return false;
}