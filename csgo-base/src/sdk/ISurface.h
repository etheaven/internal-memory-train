#pragma once
#include "../src_headers.h"
#include "Additional/Color.h"
using ulong = unsigned long;
using uc = unsigned char;
class ISurface
{
  public:
    void DrawSetColor(Color col)
    {
        typedef void(__thiscall * OrigFn)(void *, Color);
        util::getvfunc<OrigFn>(this, 14)(this, col);
    }

    void DrawSetColor(uc r, uc g, uc b, uc a = 0)
    {
        typedef void(__thiscall * OrigFn)(void *, uc, uc, uc, uc);
        util::getvfunc<OrigFn>(this, 15)(this, r, g, b, a);
    }

    void DrawFilledRect(int x0, int y0, int x1, int y1)
    {
        typedef void(__thiscall * OrigFn)(void *, int, int, int, int);
        util::getvfunc<OrigFn>(this, 16)(this, x0, y0, x1, y1);
    }

    void DrawOutlinedRect(int x0, int y0, int x1, int y1)
    {
        typedef void(__thiscall * OrigFn)(void *, int, int, int, int);
        util::getvfunc<OrigFn>(this, 18)(this, x0, y0, x1, y1);
    }

    void DrawLine(int x0, int y0, int x1, int y1)
    {
        typedef void(__thiscall * OrigFn)(void *, int, int, int, int);
        util::getvfunc<OrigFn>(this, 19)(this, x0, y0, x1, y1);
    }

    void DrawSetTextFont(ulong font)
    {
        typedef void(__thiscall * OrigFn)(void *, ulong);
        util::getvfunc<OrigFn>(this, 23)(this, font);
    }

    void DrawSetTextColor(Color col)
    {
        typedef void(__thiscall * OrigFn)(void *, Color);
        util::getvfunc<OrigFn>(this, 24)(this, col);
    }

    void DrawSetTextPos(int x, int y)
    {
        typedef void(__thiscall * OrigFn)(void *, int, int);
        util::getvfunc<OrigFn>(this, 26)(this, x, y);
    }

    void DrawPrintText(const wchar_t *text, int textLen, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT)
    {
        typedef void(__thiscall * OrigFn)(void *, const wchar_t *, int, FontDrawType);
        util::getvfunc<OrigFn>(this, 28)(this, text, textLen, drawType);
    }

    ulong CreateFont()
    {
        typedef ulong(__thiscall * OrigFn)(void *);
        return util::getvfunc<OrigFn>(this, 71)(this);
    }

    bool SetFontGlyphSet(ulong font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
    {
        typedef bool(__thiscall * OrigFn)(void *, ulong, const char *, int, int, int, int, int, int, int);
        return util::getvfunc<OrigFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
    }

    void GetTextSize(ulong font, const wchar_t *text, int &wide, int &tall)
    {
        typedef void(__thiscall * OrigFn)(void *, ulong, const wchar_t *, int &, int &);
        util::getvfunc<OrigFn>(this, 79)(this, font, text, wide, tall);
    }
};

extern ISurface *g_pSurface;