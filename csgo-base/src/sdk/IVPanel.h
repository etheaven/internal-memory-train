#pragma once

class IPanel
{
  public:
    unsigned int GetPanel(int type)
    {
        typedef unsigned int(__thiscall * tGetPanel)(void *, int type);
        return getvfunc<tGetPanel>(this, 1)(this, type);
    }
    const char *GetName(unsigned int vguiPanel)
    {
        typedef const char *(__thiscall * tGetName)(void *, unsigned int);
        return getvfunc<tGetName>(this, 37)(this, vguiPanel);
    }
};

extern IPanel *g_pPanel;