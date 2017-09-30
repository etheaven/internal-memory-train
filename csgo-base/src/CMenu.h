#pragma once

#include "sdk.h"
#include <vector>

template <typename main_value>
class MenuItem
{
public:
    int x, int y;
    wchar_t *name;
    main_value value;
    bool on = false;
};

class MenuItemManager
{
  public:
    MenuItemManager(){
        x_limit = y_limit = 900;
    }
    template <typename T>
    void Add(wchar_t *name, T value){
        MenuItem<T> item;
        if (!count){
            item.x = 120;
            item.y = 40;
            item.name = name;
            item.value = value;
            count++;
            items.push_back(std::move(item));
            return;
        }
        item.y = items[count-1].y + 20;
        item.x = items[count-1].x;
        items.push_back(item);
        count++;
    }
    int count = 0;
    int x_limit, y_limit;
    std::vector<MenuItem> items;
};

class CMenu
{
  public:
    void Init();
    void Update(); // main
  private:
    MenuItemManager manager;
};

static CMenu *menu;

CMenu::Init()
{

}