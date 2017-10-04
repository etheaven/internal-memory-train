#pragma once
using uint8_t = unsigned char;
class Color
{
  public:
    // constructors
    Color()
    {

        *((int *)this) = 0;
    }
    Color(int r, int g, int b)
    {
        SetColor((uint8_t)r, (uint8_t)g, (uint8_t)b, 255);
    }
    Color(uint8_t r, uint8_t g, uint8_t b)
    {
        SetColor(r, g, b, 255);
    }
    Color(int r, int g, int b, int a)
    {
        SetColor((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);
    }
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        SetColor(r, g, b, a);
    }
    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0)
    {
        _color[0] = (uint8_t)r;
        _color[1] = (uint8_t)g;
        _color[2] = (uint8_t)b;
        _color[3] = (uint8_t)a;
    }

    void GetColor(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const
    {
        r = _color[0];
        g = _color[1];
        b = _color[2];
        a = _color[3];
    }

    static Color FromARGB(unsigned long color)
    {
        int a = (color & 0xFF000000) >> 24;
        int r = (color & 0x00FF0000) >> 16;
        int g = (color & 0x0000FF00) >> 8;
        int b = (color & 0x000000FF);

        return Color(r, g, b, a);
    }

    void SetARGB(unsigned long color)
    {
        int a = (color & 0xFF000000) >> 24;
        int r = (color & 0x00FF0000) >> 16;
        int g = (color & 0x0000FF00) >> 8;
        int b = (color & 0x000000FF);

        SetColor(r, g, b, a);
    }

    DWORD GetARGB() const
    {
        int a = (_color[3]) >> 24;
        int r = (_color[0]) >> 16;
        int g = (_color[1]) >> 8;
        int b = (_color[2]);

        return a | r | g | b;
    }

    uint8_t &operator[](int index)
    {
        return _color[index];
    }

    const uint8_t &operator[](int index) const
    {
        return _color[index];
    }

    bool operator==(const Color &rhs) const
    {
        return (*((int *)this) == *((int *)&rhs));
    }

    bool operator!=(const Color &rhs) const
    {
        return !(operator==(rhs));
    }

    int r() { return _color[0]; }
    int g() { return _color[1]; }
    int b() { return _color[2]; }
    int a() { return _color[3]; }

    int GetR() { return _color[0]; }
    int GetG() { return _color[1]; }
    int GetB() { return _color[2]; }
    int GetA() { return _color[3]; }

    void SetR(uint8_t _i) { _color[0] = _i; }
    void SetG(uint8_t _i) { _color[1] = _i; }
    void SetB(uint8_t _i) { _color[2] = _i; }
    void SetA(uint8_t _i) { _color[3] = _i; }

    float *base()
    {
        float clr[3];

        clr[0] = (float)_color[0] / 255.f;
        clr[1] = (float)_color[1] / 255.f;
        clr[2] = (float)_color[2] / 255.f;

        return clr;
    }

    float rBase()
    {
        return (float)_color[0] / 255.f;
    }
    float gBase()
    {
        return (float)_color[1] / 255.f;
    }
    float bBase()
    {
        return (float)_color[2] / 255.f;
    }
    float aBase()
    {
        return (float)_color[3] / 255.f;
    }

    Color &operator=(const Color &rhs)
    {
        *(int *)(&_color[0]) = *(int *)&rhs._color[0];
        return *this;
    }

    Color operator+(const Color &rhs) const
    {
        int red = _color[0] + rhs._color[0];
        int green = _color[1] + rhs._color[1];
        int blue = _color[2] + rhs._color[2];
        int alpha = _color[3] + rhs._color[3];

        red = red > 255 ? 255 : red;
        green = green > 255 ? 255 : green;
        blue = blue > 255 ? 255 : blue;
        alpha = alpha > 255 ? 255 : alpha;

        return Color(red, green, blue, alpha);
    }

    Color operator-(const Color &rhs) const
    {
        int red = _color[0] - rhs._color[0];
        int green = _color[1] - rhs._color[1];
        int blue = _color[2] - rhs._color[2];
        int alpha = _color[3] - rhs._color[3];

        red = red < 0 ? 0 : red;
        green = green < 0 ? 0 : green;
        blue = blue < 0 ? 0 : blue;
        alpha = alpha < 0 ? 0 : alpha;
        return Color(red, green, blue, alpha);
    }

    operator const uint8_t *()
    {
        return (uint8_t *)(&_color[0]);
    }

  private:
    uint8_t _color[4];
};