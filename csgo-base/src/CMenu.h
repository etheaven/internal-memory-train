#pragma once

#include "sdk.h"
#include <vector>
#include <cstdio>

class IControl{
public:
  virtual void init() = 0;
  virtual void tick() = 0;
};

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
/* 
class CheckBox : public IControl
{
  public:
    void set(Mouse const *ms){
      m = ms;
    }
    void init(){}
    void tick()
    {
      if (dragged(pos, 50, 50, *m)){
        if (m->isClicked[0])
            checked = !checked;
      }
      draw();
    }
    void draw()
    {
      if (!checked)
      {
        g_pDrawManager->FillColor(pos.x, pos.y, 50, 50, Color(64,64,64));
      }
      else
      {
        g_pDrawManager->FillColor(pos.x, pos.y, 50, 50, Color(0,0,128));
      }
    }
  private:
    const Mouse *m;
    Color color;
    bool checked = false;
    Coords pos;
}; */

class CTest : public IControl
{
public:
  void set(Mouse *p){
    m = p;
  }
  void init(){

  }
  void tick(){
    g_pDrawManager->DrawRect(m->pos.x, m->pos.y, 20, 20, Color(0,255,0,128));
  }
  Mouse *m;
};

class CMenu : public IControl
{
  public:
    CMenu(){
      pos.x = pos.y = 40;
      init();
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
    CTest a;
};

void CMenu::draw_form()
{
  g_pDrawManager->FillColor(pos.x, pos.y, x_size, y_size, color);
}

void CMenu::draw_form_border()
{
    g_pDrawManager->DrawRect(pos.x, pos.y, x_size, y_size, Color(0,0,0));
}

void CMenu::init(){
  a.set(&mouse);
}

void CMenu::tick()
{
  mouse.tick();
  
  if (mouse.isClicked[0])
    pos = mouse.pos;
  draw_form();
  a.tick();
  draw_form_border();
}