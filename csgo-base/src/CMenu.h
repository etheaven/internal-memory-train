#pragma once

#include "sdk.h"
#include <vector>
#include <cstdio>


struct Coords
{
  int x = 0, y = 0;
  Coords &operator+=(const int &i)
  {
      x += i;
      y += i;
      return *this;
  }
};

struct Mouse
{
  Coords pos;
  bool isClicked[256]; // array index = virtual key code
  void tick();
  bool isdragging(Coords const &control, int x_size, int y_size);
};

class IControl
{
public:
  virtual void init() = 0;
  virtual void tick() = 0;
};


class Button : public IControl
{
public:
  Button(){ }
  void set(Mouse *m, Coords pos, int width = 20)
  {
    this->m = m;
    this->width = width * 4;
    this->height = width;
    this->pos = pos;
  }
  void init(){}
  void onClick()
  {
    printf("poop\n");
  }
  void tick()
  {
    x = pos.x;
    y = pos.y;
    draw();
    if (m->isdragging(pos, width, height))
      if (m->isClicked[1])
        onClick();
  }
  void draw()
  {
    g_pDrawManager->FillColor(pos.x, pos.y, width, height, Color(128,0,0,128));
    //g_pDrawManager->DrawString(20,20, 291, Color(0,0,0), "crashtest", false);
    g_pDrawManager->DrawString(pos.x + (x / 2), pos.y + (height / 2) - (font_height / 2), 291, Color(0,0,128,128), "Test", false);
  }
  int font_height = 14;
  int width, height;
  Mouse *m;
  Coords pos;
  int x,y;
};

void Mouse::tick()
{
  static POINT mp;
  GetCursorPos(&mp);
  ScreenToClient(GetForegroundWindow(), &mp);
  pos.x = mp.x;
  pos.y = mp.y;
  for (int i = 0; i < 256; ++i)
    isClicked[i] = GetAsyncKeyState(i) & 1; //VK_LBUTTON 0x01
}

bool Mouse::isdragging(Coords const &control, int x_size, int y_size)
{
  return this->pos.x > control.x && this->pos.y > control.y && this->pos.x < control.x + x_size && this->pos.y < control.y + y_size;
}


class CheckBox : public IControl
{
public:
  void set(Mouse *m, Coords pos, int size = 20)
  {
    this->m = m;
    this->size = size;
    this->pos = pos;
  }
  void init() {}
  void tick() 
  {
    x = pos.x;
    y = pos.y;
    if (m->isdragging(pos, size, size))
      if (m->isClicked[1])
        checked = !checked;
    draw();
  }
  void draw()
  {
    if (!checked)
      g_pDrawManager->FillColor(pos.x, pos.y, size, size, Color(128, 0, 0, 128));
    else
      g_pDrawManager->FillColor(pos.x, pos.y, size, size, Color(0, 0, 128));
    g_pDrawManager->DrawRect(pos.x, pos.y, size, size, Color(0, 0, 0));
  }

private:
  int size;
  Mouse *m;
  Color color;
  bool checked = false;
  Coords pos;
  int x,y;
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
  Button b;
  bool draw = false;
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
  last_pos += 20;
  a.set(&mouse, last_pos);
  last_pos.y += 21;
  b.set(&mouse, last_pos);
}

void CMenu::tick()
{
  mouse.tick();
  if (mouse.isClicked[0x2D])
    draw = !draw;
  if (!draw)
    return;
  /*   
  if (mouse.isClicked[0])
    pos = mouse.pos; */
  draw_form();
  a.tick();
  b.tick();
  draw_form_border();
}