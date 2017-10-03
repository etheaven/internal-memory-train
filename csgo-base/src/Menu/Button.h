#pragma once
#include "CMenu.h"
class Button : public IControl
{
public:
  Button(){ }
  void set(Mouse *m, Coords pos, int width);
  void init(){}
  void onClick();
  void tick();
  void draw();
  int font_height;
  int width, height;
  Mouse *m;
  Coords pos;
  int x,y;
};

void Button::draw()
{
  g_pDrawManager->FillColor(pos.x, pos.y, width, height, Color(128,0,0,128));
  g_pDrawManager->DrawString(pos.x + (width / 2), pos.y + (height / 2), 291, Color(0,0,128,128), "Test", true);
}

void Button::tick()
{
  x = pos.x;
  y = pos.y;
  draw();
  if (m->isdragging(pos, width, height))
    if (m->isClicked[1])
      onClick();
}
void Button::onClick()
{
  printf("poop\n");
}

void Button::set(Mouse *m, Coords pos, int width = 20)
{
  this->m = m;
  this->width = width * 4;
  this->height = width;
  this->pos = pos;
  this->font_height = 14; //TODO:
}