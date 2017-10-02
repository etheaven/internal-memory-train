#pragma once

#include "sdk.h"
#include <vector>
#include <cstdio>

class IControl
{
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
  void tick();
  bool isdragging(Coords const &control, int x_size, int y_size);
};

void Mouse::tick()
{
  static POINT mp;
  GetCursorPos(&mp);
  ScreenToClient(GetForegroundWindow(), &mp);
  pos.x = mp.x;
  pos.y = mp.y;
  for (int i = 1; i <= 2; ++i)
    isClicked[i - 1] = GetAsyncKeyState(i) & 1; //VK_LBUTTON 0x01
}

bool Mouse::isdragging(Coords const &control, int x_size, int y_size)
{
  return this->pos.x > control.x && this->pos.y > control.y && this->pos.x < control.x + x_size && this->pos.y < control.y + y_size;
}

class CheckBox : public IControl
{
public:
  void set(Mouse *m, Coords *pos, int size = 12)
  {
    this->m = m;
    this->size = size;
    this->pos = pos;
  }
  void init() {}
  void tick()
  {
    if (m->isdragging(*pos, size, size))
      if (m->isClicked[0])
        checked = !checked;
    draw();
  }
  void draw()
  {
    if (!checked)
      g_pDrawManager->FillColor(pos->x, pos->y, size, size, Color(64, 64, 64));
    else
      g_pDrawManager->FillColor(pos->x, pos->y, size, size, Color(0, 0, 128));
    g_pDrawManager->DrawRect(pos->x, pos->y, size, size, Color(0, 0, 0));
  }

private:
  int size;
  Mouse *m;
  Color color;
  bool checked = false;
  Coords *pos;
};

class CMenu : public IControl
{
public:
  CMenu()
  {
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
  Coords pos;                     // start coords
  Coords last_pos;
  Mouse mouse;
  CheckBox a;
};

void CMenu::draw_form()
{
  g_pDrawManager->FillColor(pos.x, pos.y, x_size, y_size, color);
}

void CMenu::draw_form_border()
{
  g_pDrawManager->DrawRect(pos.x, pos.y, x_size, y_size, Color(0, 0, 0));
}

void CMenu::init()
{
  last_pos = pos;
  last_pos.x += 20;
  last_pos.y += 20;
  a.set(&mouse, &last_pos);
}

void CMenu::tick()
{
  mouse.tick();
  /*   
  if (mouse.isClicked[0])
    pos = mouse.pos; */
  draw_form();
  a.tick();
  draw_form_border();
}