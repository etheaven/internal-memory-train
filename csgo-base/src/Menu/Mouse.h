#pragma once
#include "Coords.h"

class Mouse
{
public:
  Coords pos;
  bool isClicked[256]; // array index = virtual key code
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
  for (int i = 0; i < 256; ++i)
    isClicked[i] = GetAsyncKeyState(i) & 1; //VK_LBUTTON 0x01
}

bool Mouse::isdragging(Coords const &control, int x_size, int y_size)
{
  return this->pos.x > control.x && this->pos.y > control.y && this->pos.x < control.x + x_size && this->pos.y < control.y + y_size;
}
