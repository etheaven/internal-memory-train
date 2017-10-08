#pragma once

#include "../sdk.h"
#include <vector>
#include <cstdio>

#include "Coords.h"
#include "Mouse.h"
#include "IControl.h"
#include "Button.h"
#include "CheckBox.h"

class MenuItem{
public:
  MenuItem(const char *n = "", const Coords pos = Coords(0,0)){
    set(n,pos);
  }
  void set(const char *n = "", const Coords pos = Coords(0,0)){
    this->name = n;
    this->pos = pos;
    enabled = false;
  }
  void tick(){
    g_pDrawManager->DrawString(pos.x, pos.y, 291, Color(255,255,255,255), name, false);
    g_pDrawManager->DrawString(pos.x + 40, pos.y, 291, Color(255,0,0), "OFF", false);
  } 
  const char *name;
  Coords pos;
  bool enabled;
};

class FeatureHandler{
public:
  void tick(){
    for(const auto& f : items)
      f->tick();
  }
  std::vector<MenuItem*> items;
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
  void draw_heading();
  void draw_form();
  void draw_form_border();

private:
  Color color = Color(0, 0, 128, 64);
  int x_size = 500, y_size = 400; // x2,y2
  Coords pos;                     // start coords
  Coords last_pos;
  Mouse mouse;
  bool draw = false;
  char *head_title;
  unsigned long head_font;
  MenuItem cf_rcs, cf_aim;
  FeatureHandler handler;
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
  cf_rcs.set("RCS", Coords(last_pos.x + 40, last_pos.y + 40));
  cf_aim.set("AIM", Coords(last_pos.x + 40, last_pos.y + 60));
  handler.items.push_back(&cf_rcs);
  handler.items.push_back(&cf_aim);
}

void CMenu::tick()
{
  mouse.tick();
  if (mouse.isClicked[0x2D])
    draw = !draw;
  if (!draw)
    return;
  static Coords t_pos = last_pos;
  
  last_pos = t_pos;
    g_pDrawManager->DrawString(last_pos.x, last_pos.y, 291, Color(128,0,128,220), "Milky way", false);
    handler.tick();

}