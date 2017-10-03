#pragma once
#include "CMenu.h"
class CheckBox : public IControl
{
public:
    void set(Mouse *m, Coords pos, int size);
    void init();
    void tick();
    void draw();

private:
  int size;
  Mouse *m;
  Color color;
  bool checked = false;
  Coords pos;
  int x,y;
};

void CheckBox::set(Mouse *m, Coords pos, int size = 20)
{
  this->m = m;
  this->size = size;
  this->pos = pos;
}

void CheckBox::init() {}

void CheckBox::tick() 
{
  x = pos.x;
  y = pos.y;
  if (m->isdragging(pos, size, size))
    if (m->isClicked[1])
      checked = !checked;
  draw();
}


void CheckBox::draw()
{
  if (!checked)
    g_pDrawManager->FillColor(pos.x, pos.y, size, size, Color(128, 0, 0, 128));
  else
    g_pDrawManager->FillColor(pos.x, pos.y, size, size, Color(0, 0, 128));
  g_pDrawManager->DrawRect(pos.x, pos.y, size, size, Color(0, 0, 0));
}