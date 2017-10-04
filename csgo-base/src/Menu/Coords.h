#pragma once


class Coords
{
public:
  Coords(int x = 0, int y = 0){
    this->x = x;
    this->y = y;
  }
  int x, y;
  Coords &operator+=(const int &i);
  Coords operator+(const int &i);
};

Coords &Coords::operator+=(const int &i)
{
    x += i;
    y += i;
    return *this;
}


Coords Coords::operator+(const int &i)
{
    return Coords(this->x + i, this->y + i);
}
