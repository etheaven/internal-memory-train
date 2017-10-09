#pragma once
#include "src_headers.h"
#include "constants/definitions.h"
#include "math.h"
#include "Menu/CMenu.h"

#include <cstdio>
CMenu menu;
DrawManager *g_pDrawManager;
void __fastcall hkPaintTraverse(void *pPanel, void *unk, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
    oPaintTraverse(pPanel, vguiPanel, forceRepaint, allowForce);
    
    static auto panelId = 0;
    static DWORD UI_Font;
    if (!panelId)
    {
        const auto panelName = g_pPanel->GetName(vguiPanel);
        if (!strcmp(panelName, "FocusOverlayPanel"))
        {
            panelId = vguiPanel;
            UI_Font = g_pSurface->CreateFont();
            g_pSurface->SetFontGlyphSet(UI_Font, "Verdana", 14, 150, 0, 0, FontDrawType_t::FONTFLAG_OUTLINE);
        }
    }
    else if (panelId == vguiPanel)
    {
        int width, height;
        g_pEngine->GetScreenSize(width, height);
        if (g_pEngine->IsConnected() && g_pEngine->IsInGame())
        {
            CEntity *pLocalPlayer = g_pEntityList->getcliententity(g_pEngine->GetLocalBase());
            for (int i = 0; i < g_pEngine->GetMaxClients(); ++i)
            {
                CEntity *pEntity = (CEntity *)g_pEntityList->getcliententity(i);
                if (!pEntity)
                    continue;
                if (pEntity == pLocalPlayer)
                    continue;
                if (pEntity->isdormant())
                    continue;
                if (pEntity->gethealth() < 1)
                    continue;
                if (pEntity->getteam() == pLocalPlayer->getteam())
                    continue;

                const Vector bottom = pLocalPlayer->getorigin();
                const Vector top = pEntity->GetBonePosition(8);
                Vector screenBot, screenTop;
                if (W2S(bottom, screenBot) && W2S(top, screenTop))
                {
                    g_pDrawManager->DrawRect(screenTop.x, screenTop.y, 2, 2, Color(255, 0, 0, 200));
                }
            }
        }
        menu.tick();
    }
}