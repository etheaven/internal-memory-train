#pragma once
#include "src_headers.h"
#include "constants/definitions.h"

#include <cstdio>

DrawManager *g_pDrawManager;
void __fastcall hkPaintTraverse(void *pPanel, void *unk, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
    oPaintTraverse(pPanel, vguiPanel, forceRepaint, allowForce);
    static auto panelId = 0;
    static DWORD UI_Font;
    if (!panelId)
    {
        const auto panelName = g_pPanel->GetName(vguiPanel);
        printf("panel: %s\n", panelName);
        if (!strcmp(panelName, "FocusOverlayPanel"))
        {
            panelId = vguiPanel;
            UI_Font = g_pSurface->CreateFont();
            g_pSurface->SetFontGlyphSet(UI_Font, "Verdana", 14, 150, 0, 0, FontDrawType_t::FONTFLAG_OUTLINE);
        }
    }
    else if (panelId == vguiPanel)
    {
        g_pDrawManager->TextW(true, UI_Font, 100, 50, Color(255, 0, 0, 255), L"test abcaa1564891");
    }
}