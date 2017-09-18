#pragma once
#include <cmath>
typedef float vec_t;
class Vector
{
  public:
    Vector();
    Vector(float, float, float);

    float &operator[](int);
    Vector &operator=(const Vector &);

    Vector &operator+=(const Vector &);
    Vector &operator-=(const Vector &);
    Vector &operator*=(const Vector &);
    Vector &operator*=(const float);
    Vector &operator/=(const Vector &);
    Vector &operator/=(const float);

    Vector operator+(const Vector &) const;
    Vector operator-(const Vector &) const;

    Vector operator*(const Vector &)const;
    Vector operator*(const float &)const;

    Vector operator/(const Vector &) const;
    Vector operator/(const float &) const;

    bool operator!=(const float &);
    void clamp();
    inline float Length() const;
    vec_t Length2D() const;
    vec_t Length2DSqr() const;
    vec_t DistTo(Vector &vOther);
    void VectorSubtract(Vector const &a, Vector const &b, Vector &c);
    float isqrt(float x);
    float x, y, z;
};

inline float isqrt(float x)
{
    return (sqrtf(x));
}

inline vec_t Vector::DistTo(Vector &vOther)
{
    Vector delta = (*this - vOther); //VectorSubtract(*this, vOther, delta);
    return delta.Length();
}

inline float VectorLength(const Vector &v)
{
    return (float)isqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vec_t Vector::Length(void) const
{
    return VectorLength(*this);
}

inline vec_t Vector::Length2D() const
{
    return (vec_t)::sqrtf(this->x * this->x + this->y * this->y);
}

inline vec_t Vector::Length2DSqr() const
{
    return (this->x * this->x + this->y * this->y);
}

Vector::Vector()
{
    x = y = z = 0.f;
}

Vector::Vector(float ix, float iy, float iz)
{
    x = ix;
    y = iy;
    z = iz;
}

Vector &Vector::operator=(const Vector &i)
{
    x = i.x;
    y = i.y;
    z = i.z;
    return *this;
}

Vector &Vector::operator+=(const Vector &i)
{
    x += i.x;
    y += i.y;
    z += i.z;
    return *this;
}

Vector &Vector::operator-=(const Vector &i)
{
    x -= i.x;
    y -= i.y;
    z -= i.z;
    return *this;
}

Vector &Vector::operator*=(const Vector &i)
{
    x *= i.x;
    y *= i.y;
    z *= i.z;
    return *this;
}

Vector &Vector::operator*=(const float i)
{
    x *= i;
    y *= i;
    z *= i;
    return *this;
}

Vector &Vector::operator/=(const Vector &i)
{
    x /= i.x;
    y /= i.y;
    z /= i.z;
    return *this;
}

Vector &Vector::operator/=(const float i)
{
    x /= i;
    y /= i;
    z /= i;
    return *this;
}

Vector Vector::operator+(const Vector &i) const
{
    return Vector(x + i.x, y + i.y, z + i.z);
}

Vector Vector::operator-(const Vector &i) const
{
    return Vector(x - i.x, y - i.y, z - i.z);
}

Vector Vector::operator*(const Vector &i) const
{
    return Vector(x * i.x, y * i.y, z * i.z);
}

Vector Vector::operator*(const float &i) const
{
    return Vector(x * i, y * i, z * i);
}

Vector Vector::operator/(const Vector &i) const
{
    return Vector(x / i.x, y / i.y, z / i.z);
}

Vector Vector::operator/(const float &i) const
{
    return Vector(x / i, y / i, z / i);
}

bool Vector::operator!=(const float &x)
{
    return this->x != x || this->y != x;
}

void Vector::clamp()
{
    if (this->x > 89.0f && this->x <= 180.0f)
    {
        this->x = 89.0f;
    }
    while (this->x > 180.f)
    {
        this->x -= 360.f;
    }
    while (this->x < -89.0f)
    {
        this->x = -89.0f;
    }
    while (this->y > 180.f)
    {
        this->y -= 360.f;
    }
    while (this->y < -180.f)
    {
        this->y += 360.f;
    }
}

using vec3f = Vector;