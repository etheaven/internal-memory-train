#pragma once
#include "src_headers.h"
#include "constants/definitions.h"

#include <cstdlib>

void __fastcall hkPaintTraverse(void *pPanel, void *unk, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
    oPaintTraverse(pPanel, vguiPanel, forceRepaint, allowForce);
    auto *szName = g_pPanel->GetName(vguiPanel);
    static DWORD MatSystemTopPanel;
    static DWORD UI_Font;

    printf("%s\n", szName);
}