#pragma once

#include "../sdk.h"
#include "../sdk/ISurface.h"

#include <cstdlib>
#include "wchar.h"
#include <string>

namespace DrawUtils
{
const wchar_t *charToWchar_t(const char *text, int *out)
{
	int i = 0;
	for (; text[i] != '\0'; ++i);
	auto ws = std::wstring(&text[0], &text[i]);
	const wchar_t *p = (ws.c_str());
	*out = i;
	return p;
}
}

class DrawManager
{
  public:
	DrawManager(){};
	void FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
	{
		g_pSurface->DrawSetColor(r, g, b, a);
		g_pSurface->DrawFilledRect(x, y, x + w, y + h);
	}
	void FillColor(int x, int y, int w, int h, Color c)
	{
		g_pSurface->DrawSetColor(c);
		g_pSurface->DrawFilledRect(x, y, x + w, y + h);
	}
	void DrawHealthBox(int x, int y, int r, int g, int b, int CurHealth, int MaxHealth)
	{
		float mx = MaxHealth / 4;
		float wx = CurHealth / 4;
		if (mx == 0)
			return;
		x -= (mx / 2);
		this->FillRGBA(x - 1, y - 1, mx + 2, 4 + 2, r, g, b, 255);
		this->FillRGBA(x, y, wx, 4, r, g, b, 255);
	}
	void DrawLine(int x0, int y0, int x1, int y1, Color c)
	{
		g_pSurface->DrawSetColor(c);
		g_pSurface->DrawLine(x0, y0, x1, y1);
	}
	void DrawRect(int X, int Y, int W, int H, Color Color)
	{
		g_pSurface->DrawSetColor(Color);
		g_pSurface->DrawOutlinedRect(X, Y, X + W, Y + H);
	}

	void DrawInlineRect(int X, int Y, int W, int H, Color color)
	{
		DrawRect(X, Y, W, H, color);
		DrawRect(X + 1, Y + 1, W - 2, H - 2, Color(0, 0, 0, 255));
		DrawRect(X - 1, Y - 1, W + 2, H + 2, Color(0, 0, 0, 255));
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1, int R, int G, int B, int A)
	{
		auto BoxWidth = x1 - x0;
		auto BoxHeight = y1 - y0;

		g_pSurface->DrawSetColor(R, G, B, A);

		g_pSurface->DrawFilledRect(x0, y0, x0 + (BoxWidth / 5), y0 + 1);  //left top
		g_pSurface->DrawFilledRect(x0, y0, x0 + 1, y0 + (BoxHeight / 6)); //left top

		g_pSurface->DrawFilledRect(x1 - (BoxWidth / 5) + 1, y0, x1, y0 + 1); //right top
		g_pSurface->DrawFilledRect(x1, y0, x1 + 1, y0 + (BoxHeight / 6));	//right top

		g_pSurface->DrawFilledRect(x0, y1, x0 + (BoxWidth / 5), y1 + 1);		  //left bottom
		g_pSurface->DrawFilledRect(x0, y1 - (BoxHeight / 6) + 1, x0 + 1, y1 + 1); //left bottom

		g_pSurface->DrawFilledRect(x1 - (BoxWidth / 5) + 1, y1, x1, y1 + 1);	  //right bottom
		g_pSurface->DrawFilledRect(x1, y1 - (BoxHeight / 6) + 1, x1 + 1, y1 + 1); //right bottom
	}

	void boxESP(int x, int y, int radius, int R, int G, int B)
	{
		int iStep = (radius * 4);

		for (int i = 0; i < radius; i++)
		{

			//Background
			FillRGBA((x - iStep + i) - 1, (y - iStep) - 1, 3, 3, 0, 0, 0, 255);
			FillRGBA((x - iStep) - 1, (y - iStep + i) - 1, 3, 3, 0, 0, 0, 255);

			FillRGBA((x + iStep - i) - 1, (y - iStep) - 1, 3, 3, 0, 0, 0, 255);
			FillRGBA((x + iStep) - 1, (y - iStep + i) - 1, 3, 3, 0, 0, 0, 255);

			FillRGBA((x - iStep + i) - 1, (y + iStep) - 1, 3, 3, 0, 0, 0, 255);
			FillRGBA((x - iStep) - 1, (y + iStep - i) - 1, 3, 3, 0, 0, 0, 255);

			FillRGBA((x + iStep - i) - 1, (y + iStep) - 1, 3, 3, 0, 0, 0, 255);
			FillRGBA((x + iStep) - 1, (y + iStep - i) - 1, 3, 3, 0, 0, 0, 255);
		}

		for (int i = 0; i < radius; i++)
		{

			//Simple
			FillRGBA(x - iStep + i, y - iStep, 1, 1, R, G, B, 255);
			FillRGBA(x - iStep, y - iStep + i, 1, 1, R, G, B, 255);

			FillRGBA(x + iStep - i, y - iStep, 1, 1, R, G, B, 255);
			FillRGBA(x + iStep, y - iStep + i, 1, 1, R, G, B, 255);

			FillRGBA(x - iStep + i, y + iStep, 1, 1, R, G, B, 255);
			FillRGBA(x - iStep, y + iStep - i, 1, 1, R, G, B, 255);

			FillRGBA(x + iStep - i, y + iStep, 1, 1, R, G, B, 255);
			FillRGBA(x + iStep, y + iStep - i, 1, 1, R, G, B, 255);
		}
	}

	void drawCrosshair(int x, int y, int r, int g, int b)
	{
		//Right
		FillRGBA(x, y, 15, 2, r, g, b, 255);
		//Bottom
		FillRGBA(x, y, 2, 15, r, g, b, 255);
		//Left
		FillRGBA(x - 15, y, 15, 2, r, g, b, 255);
		//Top
		FillRGBA(x, y - 15, 2, 15, r, g, b, 255);
	}

	void DrawBox(int x, int y, int w, int h, int lw, int r, int g, int b, int a)
	{
		FillRGBA(x, y, w, lw, r, g, b, a);						  // top
		FillRGBA(x, y + lw, lw, h - lw, r, g, b, a);			  // left
		FillRGBA(x + w - lw, y + lw, lw, h - lw, r, g, b, a);	 // right
		FillRGBA(x + lw, y + h - lw, w - lw * 2, lw, r, g, b, a); // bottom
	}

	void DrawStringWide(int x, int y, int font, Color const &c, const wchar_t *text, int text_len, bool centre)
	{
		if (centre)
		{
			static int wide, tall;
			g_pSurface->GetTextSize(font, text, wide, tall);
			x -= wide / 2;
			y -= tall / 2;
		}
		static Color c_curr;
		static int font_curr;
		if (!c_curr || c_curr != c)
			c_curr = c;
		if (!font_curr || font_curr != font)
			font_curr = font;

		g_pSurface->DrawSetTextPos(x, y);
		g_pSurface->DrawSetTextFont(font_curr);
		g_pSurface->DrawSetTextColor(c_curr);
		g_pSurface->DrawPrintText(text, text_len);
	}

	void DrawString(int x, int y, int font, Color const &c, const char *text, bool centre)
	{
		static int m_font;
		if (m_font < 1)
		{
			if (m_font == -1 && font == -1) // means we wait for font from other side
				return;
			if (m_font == -1)
				m_font = font;
		}
		int i = 0;
		for (; text[i] != '\0'; ++i)
			;
		auto ws = std::wstring(&text[0], &text[i]);
		const wchar_t *p = (ws.c_str());
		this->DrawStringWide(x, y, font, c, p, i, centre);
	}
};

extern DrawManager *g_pDrawManager;