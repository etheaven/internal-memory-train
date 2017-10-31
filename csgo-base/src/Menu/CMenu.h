#pragma once

#include "../sdk.h"
#include <vector>
#include <cstdio>

#include "Coords.h"
#include "Mouse.h"

class Feature
{
public:
  enum Name
  {
    RCS = 0,
    AIM,
    DESP,
    ESP,
    BHOP,
    TRIG,
  };
  static const char *getc_str(Feature::Name name)
  {
    switch (name)
    {
    case RCS:
      return " RCS";
    case AIM:
      return " AIM";
    case DESP:
      return "DESP";
    case ESP:
      return " ESP";
    case BHOP:
      return "BHOP";
    case TRIG:
      return "TRIG";

    default:
      return "Unknown";
    }
  }
};

class MenuItem
{
public:
  MenuItem(const char *n = "", const Coords pos = Coords(0, 0))
  {
    set(n, pos);
  }
  void set(const char *n = "", const Coords pos = Coords(0, 0))
  {
    this->name = n;
    this->pos = pos;
    enabled = false;
    common = Color(255, 255, 255, 255);
    hl = Color(128, 0, 0, 255);
    is_hl = false;
  }
  void highlight()
  {
    if (is_hl)
      is_hl = false;
    else
      is_hl = true;
  }
  bool toggle()
  {
    enabled = enabled ? false : true;
  }
  void tick()
  {
    Color c = (is_hl ? hl : common);
    g_pDrawManager->DrawString(pos.x, pos.y, 291, c, name, false);
    static const char *msg = "OFF";
    static Color clr = Color(255, 255, 255);
    if (enabled)
    {
      clr = Color(255, 0, 0);
      msg = "ON";
    }
    else
    {
      clr = Color(255, 255, 255);
      msg = "OFF";
    }
    g_pDrawManager->DrawString(pos.x + 40, pos.y, 291, clr, msg, false);
  }
  Color hl;
  bool is_hl;
  Color common;
  const char *name;
  Coords pos;
  bool enabled;
};

class FeatureHandler
{
public:
  FeatureHandler()
  {
    i_currFeature = 0;
  }
  void tick()
  {
    for (const auto &f : items)
      f->tick();
  }
  void change(int index)
  {
    if (index < 0)
      return;
    if (index > this->items.size() - 1) //reset
      return;
    items.at(i_currFeature)->highlight();
    if (i_currFeature != index) // no on-off aka always off
      items.at(index)->highlight();
    i_currFeature = index;
  }
  // 11 wrong access
  int toggle(unsigned id)
  {
    if (id > this->items.size() - 1)
      return 11;
    return items.at(id)->toggle(); // else 1 or 0
  }

  int get_id(const char *name)
  {
    int i = 0;
    for (const auto el : items)
    {
      if (strcmp(el->name, name))
        return i;
      i++;
    }
  }

  int i_currFeature;
  std::vector<MenuItem *> items;
};

class CMenu
{
public:
  CMenu()
  {
    pos.x = pos.y = 40;
    init();
  }
  void init();
  void tick();

  Color color = Color(0, 0, 128, 64);
  int x_size = 500, y_size = 400; // x2,y2
  Coords pos;                     // start coords
  Coords last_pos;
  Mouse mouse;
  bool draw = false;
  unsigned long head_font;
  MenuItem cf_rcs, cf_aim, cf_dotesp, cf_bhop, cf_trigger;
  FeatureHandler handler;
} * g_pMenu;

void CMenu::init()
{
  last_pos = pos;
  last_pos += 40;
  //TODO: global constant name to search in memory
  cf_rcs.set(Feature::getc_str(Feature::Name::RCS), Coords(last_pos.x + 40, last_pos.y + 40));
  handler.items.push_back(&cf_rcs);
  cf_aim.set(Feature::getc_str(Feature::Name::AIM), Coords(last_pos.x + 40, last_pos.y + 60));
  handler.items.push_back(&cf_aim);
  cf_dotesp.set(Feature::getc_str(Feature::Name::DESP), Coords(last_pos.x + 40, last_pos.y + 80));
  handler.items.push_back(&cf_dotesp);
  cf_bhop.set(Feature::getc_str(Feature::Name::BHOP), Coords(last_pos.x + 40, last_pos.y + 100));
  handler.items.push_back(&cf_bhop);
  cf_trigger.set(Feature::getc_str(Feature::Name::TRIG), Coords(last_pos.x + 40, last_pos.y + 120));
  handler.items.push_back(&cf_trigger);

  handler.change(handler.i_currFeature);
}

void CMenu::tick()
{
  mouse.tick();
  if (mouse.isClicked[0x2D])
    draw = !draw;
  if (!draw)
    return;
  if (mouse.isClicked[VK_UP])
    handler.change(handler.i_currFeature - 1);
  if (mouse.isClicked[VK_DOWN])
    handler.change(handler.i_currFeature + 1);
  if (mouse.isClicked[VK_RIGHT] || mouse.isClicked[VK_LEFT])
    handler.toggle(handler.i_currFeature);

  g_pDrawManager->DrawString(last_pos.x, last_pos.y, 291, Color(192, 0, 64, 220), "Milky way", false);
  handler.tick();
}