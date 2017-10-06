#pragma once

#include "../sdk.h"
#include <vector>
#include <cstdio>

#include "Coords.h"
#include "Mouse.h"
#include "IControl.h"
#include "Button.h"
#include "CheckBox.h"

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
  void draw_heading();
  void draw_form();
  void draw_form_border();

private:
  Color color = Color(0, 0, 128, 64);
  int x_size = 500, y_size = 400; // x2,y2
  Coords pos;                     // start coords
  Coords last_pos;
  Mouse mouse;
/*   CheckBox a;
  Button b; */
  ButtonString bs;
  bool draw = false;
  char *head_title;
  unsigned long head_font;
};

void CMenu::draw_form()
{
  draw_heading();
  g_pDrawManager->FillColor(pos.x, pos.y, x_size, y_size, color);
}

void CMenu::draw_form_border()
{
  g_pDrawManager->DrawRect(pos.x, pos.y, x_size, y_size, Color(0, 0, 0));
}

void CMenu::draw_heading()
{
  g_pDrawManager->FillColor(pos.x, pos.y, x_size, 28, Color(16, 173, 237, 96));
  g_pDrawManager->DrawString(pos.x + (x_size / 2), pos.y + 28 / 2 + 7, 291, Color(196, 0, 0, 220), head_title, true);
}

void CMenu::init()
{
  head_title = "nice mem";
  last_pos = pos;
  last_pos += 40;
/*   a.set(&mouse, last_pos);
  last_pos.y += 21;
  b.set(&mouse, last_pos); */
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
/*   a.tick();
  b.tick(); */
  //bs.tick();
  draw_form_border();
}