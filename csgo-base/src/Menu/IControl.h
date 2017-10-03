#pragma once

class IControl
{
public:
  virtual void init() = 0;
  virtual void tick() = 0;
};