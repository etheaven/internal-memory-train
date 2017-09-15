#pragma once
class vec3f
{
public:
    float x, y, z;

  public:
    vec3f(float x = 0.0f, float y = 0.0f, float z = 0.0f)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void clamp()
    {
        if (this->x > 89.0f && this->x <= 180.0f)
            this->x = 88.0f;

        if (this->x > 180.0f)
            this->x = this->x - 360.0f;

        if (this->x < -89.0f)
            this->x = -88.0f;

        if (this->y > 180.0f)
            this->y = this->y - 360.0f;

        if (this->y < -180.0f)
            this->y = this->y + 360.0f;
        //assert(!(this->z > 0));
    }
    vec3f &operator+=(vec3f a)
    {
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;
        return *this;
    }
    vec3f &operator-=(vec3f a)
    {
        this->x -= a.x;
        this->y -= a.y;
        this->z -= a.z;
        return *this;
    }
    vec3f &operator+(vec3f const &b)
    {
        return *this += b;
    }
    vec3f &operator*(vec3f const &b)
    {
        this->x = this->x * b.x;
        this->y = this->y * b.y;
        this->z = this->z * b.z;
        return *this;
    }
    vec3f &operator*(float &b)
    {
        vec3f tmp(this->x * b, this->y * b, this->z * b);
        return tmp;
    }
    vec3f &operator*=(vec3f const &b)
    {
        /* this->x *= b.x;
        this->y *= b.y;
        this->z *= b.z; */
        return (*this = *this * b);
    }
};

using Vector = vec3f;