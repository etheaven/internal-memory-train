#pragma once


struct Coords
{
  int x = 0, y = 0;
  Coords &operator+=(const int &i);
};

Coords &Coords::operator+=(const int &i)
{
    x += i;
    y += i;
    return *this;
}