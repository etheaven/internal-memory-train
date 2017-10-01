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
  void tick()
  {
    static POINT mp;
    GetCursorPos(&mp);
    ScreenToClient(GetForegroundWindow(), &mp);
    pos.x = mp.x;
    pos.y = mp.y;
    for(int i = 1; i <= 2; ++i)
      isClicked[i-1] = GetAsyncKeyState(i);
  }
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
      if (!checked)
      {
        g_pDrawManager->FillColor(pos.x, pos.y, 12, 12, color);
      }
      else
      {
        g_pDrawManager->FillColor(pos.x, pos.y, 12, 12, Color(0,0,255));
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
    void draw_form();
    void draw_form_border();
  private:
    Color color = Color(0, 128, 0, 64);
    int x_size = 500, y_size = 400; // x2,y2
    Coords pos; // start coords
    Mouse mouse;
};

void CMenu::draw_form()
{
  g_pDrawManager->FillColor(pos.x, pos.y, x_size, y_size, color);
}

void CMenu::draw_form_border()
{
    g_pDrawManager->DrawRect(pos.x, pos.y, x_size, y_size, Color(0,0,0));
}

void CMenu::tick()
{
  mouse.tick();
  
  if (mouse.isClicked[0])
    pos = mouse.pos;
  draw_form();

  draw_form_border();
}