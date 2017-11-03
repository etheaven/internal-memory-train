#pragma once
#include <cmath>
#include <algorithm>
typedef float vec_t;
class Vector
{
  public:
    Vector();
    Vector(float, float, float);

    float &operator[](int i);
    float operator[](int i) const;

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
    void NormalizeAngles();
    float isqrt(float x);
    vec_t DotProduct(const Vector &a, const Vector &b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    inline vec_t Dot(const Vector &vOther)
    {
        return DotProduct(*this, vOther);
    }
    inline void Init(vec_t ix, vec_t iy, vec_t iz)
    {
        x = ix;
        y = iy;
        z = iz;
    }
    inline vec_t VectorLength(const Vector &v)
    {
        return (vec_t)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    inline vec_t Length(void)
    {
        return VectorLength(*this);
    }
    inline vec_t Length2D(void)
    {
        return (vec_t)::sqrtf(x * x + y * y);
    }
    inline vec_t VectorNormalize(Vector &v)
    {
        vec_t l = v.Length();

        if (l != 0.0f)
        {
            v /= l;
        }
        else
        {
            v.x = v.y = 0.0f;
            v.z = 1.0f;
        }

        return l;
    }

    inline float VectorNormalizer(float *v)
    {
        return VectorNormalize(*(reinterpret_cast<Vector *>(v)));
    }
    inline vec_t NormalizeInPlace()
    {
        return VectorNormalize(*this);
    }

    float x, y, z;
};

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
    this->z = 0.0f;
}

void Vector::NormalizeAngles()
{
    if (this->x < -89.0f)
        this->x = -89.0f;

    if (this->x > 89.0f)
        this->x = 89.0f;

    while (this->y < -180.0f)
        this->y += 360.0f;

    while (this->y > 180.0f)
        this->y -= 360.0f;

    this->z = 0.0f;
}

float &Vector::operator[](int i)
{
    return ((float *)this)[i];
}

float Vector::operator[](int i) const
{
    return ((float *)this)[i];
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

#define PI 3.14159265358979323846f
#define DEG2RAD(x) ((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x) ((float)(x) * (float)(180.0f / (float)(PI)))
#define RADPI 57.295779513082f
#define rad(a) a * 0.01745329251
using vec3f = Vector;

class VectorAligned : public vec3f
{
public:
	VectorAligned( ) {}

	VectorAligned( const Vector &vec )
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	float w;
};