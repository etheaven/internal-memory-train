#pragma once

#include "sdk.h"
#include <vector>
#include <cstdio>

struct Coords
{
  int x = 0, y = 0;
};
struct Mouse
{
  Coords pos;
  bool isClicked[2];
};

bool dragged(Coords const& control, int x_size, int y_size, Mouse const& mouse)
{
  return mouse.pos.x > control.x && mouse.pos.y > control.y && mouse.pos.x < control.x + x_size && mouse.pos.y < control.y + y_size;
}

class CheckBox 
{
  public:
    CheckBox(int x = 0, int y = 0)
    {
      pos.x = x;
      pos.y = y;
    }
    void tick(Mouse const& m)
    {
      if (dragged(pos, 12, 12, m)){
        if (m.isClicked[0])
          checked = true;
        else checked = false;
      }
      else
        checked = false;
      draw();
    }
    void draw()
    {
      if (!checked){
        g_pSurface->DrawSetColor(color);
        g_pSurface->DrawFilledRect(pos.x, pos.x + 12, pos.y, pos.y + 12);
      }
      else{
        g_pSurface->DrawSetColor(Color(0,0,255));
        g_pSurface->DrawFilledRect(pos.x, pos.x + 12, pos.y, pos.y + 12);
      }
    }
  private:
    Color color;
    bool checked = false;
    Coords pos;
};

class CMenu
{
  public:
    CMenu(){
      pos.x = pos.y = 40;
    }
    void init();
    void tick();
    void update_mouse();
    void draw_form();
    void draw_form_border();
  private:
    Color color = Color(0, 128, 0, 64);
    int x_size = 500, y_size = 400; // x2,y2
    Coords pos; // start coords
    Mouse mouse;
    CheckBox cb1;
};

void CMenu::update_mouse()
{
  POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
  mouse.pos.x = mp.x;
  mouse.pos.y = mp.y;
  for(int i = 1; i <= 2; ++i)
    mouse.isClicked[i-1] = GetAsyncKeyState(i);
}

void CMenu::draw_form()
{
  g_pSurface->DrawSetColor(color);
  g_pSurface->DrawFilledRect(pos.x, pos.x + x_size, pos.y, pos.y + y_size);
}

void CMenu::draw_form_border()
{
    g_pDrawManager->DrawRect(pos.x, pos.y, x_size, y_size, Color(0,0,0));
}

void CMenu::tick()
{
  update_mouse();
  draw_form();
  cb1.tick(mouse);
  draw_form_border();
}