#pragma once
#include "src_headers.h"
#include "constants/definitions.h"
#include "math.h"

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
        if (g_pEngine->IsConnected() && g_pEngine->IsInGame())
        {
            int width, height;
            g_pEngine->GetScreenSize(width, height);
            CEntity *pLocalPlayer = g_pEntityList->getcliententity(g_pEngine->GetLocalBase());
            for (int i = 0; i < g_pEngine->GetMaxClients(); ++i)
            {
                CEntity *pEntity = (CEntity *)g_pEntityList->getcliententity(i);
                if (!pEntity)
                    continue;
                if (pEntity == pLocalPlayer)
                    continue;

                const Vector bottom = pEntity->getabsorigin();
                const Vector top = pEntity->GetBonePosition(6);
                Vector screenBot, screenTop;
                if (W2S(bottom, screenBot) && W2S(top, screenTop))
                {
                    
                    g_pDrawManager->boxESP(screenTop.x, screenTop.y, 20, 255, 0, 0);
                }
            }
        }
    }
}