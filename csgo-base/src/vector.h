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
    /* inline float Length();
    vec_t Length2D() const;
    vec_t Length2DSqr() const;
    vec_t DistTo(Vector &vOther);
    vec_t DotProduct(const Vector &a, const Vector &b);
    vec_t Dot(const Vector &vOther);
    float VectorLength(const Vector &v); */
    //void VectorSubtract(Vector const &a, Vector const &b, Vector &c);
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
/* 
inline float Vector::isqrt(float x)
{
    return (sqrtf(x));
}

inline vec_t Vector::DistTo(Vector &vOther)
{
    Vector delta = (*this - vOther); //VectorSubtract(*this, vOther, delta);
    return delta.Length();
}

inline float Vector::VectorLength(const Vector &v)
{
    return (float)isqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vec_t Vector::Length(void)
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
} */

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
/* 
inline vec_t Vector::DotProduct(const Vector &a, const Vector &b)
{inline vec_t DotProduct(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec_t Dot(const Vector& vOther) const
{
	return DotProduct(*this, vOther);
}

    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec_t Vector::Dot(const Vector &vOther)
{
    return DotProduct(*this, vOther);
}


void SinCos(float a, float *s, float *c)
{
    *s = sin(a);
    *c = cos(a);
}

void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up)
{
    float sr, sp, sy, cr, cp, cy;

    SinCos(DEG2RAD(angles.y), &sy, &cy);
    SinCos(DEG2RAD(angles.x), &sp, &cp);
    SinCos(DEG2RAD(angles.z), &sr, &cr);

    if (forward)
    {
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    if (right)
    {
        right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
        right->y = (-1 * sr * sp * sy + -1 * cr * cy);
        right->z = -1 * sr * cp;
    }

    if (up)
    {
        up->x = (cr * sp * cy + -sr * -sy);
        up->y = (cr * sp * sy + -sr * cy);
        up->z = cr * cp;
    }
}

void Normalize(Vector &vIn, Vector &vOut)
{
    float flLen = vIn.Length();
    if (flLen == 0)
    {
        vOut = Vector(0.f, 0.f, 1.f);
        return;
    }
    flLen = 1 / flLen;
    vOut = Vector(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

void AngleVectors(const Vector &angles, Vector *forward)
{

    float sp, sy, cp, cy;

    sy = sin(DEG2RAD(angles.y));
    cy = cos(DEG2RAD(angles.y));

    sp = sin(DEG2RAD(angles.x));
    cp = cos(DEG2RAD(angles.x));

    forward->x = cp * cy;
    forward->y = cp * sy;
    forward->z = -sp;
} */

using vec3f = Vector;