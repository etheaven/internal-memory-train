#pragma once
class vec3f
{

    float x, y, z;
public:
    vec3f &operator+=(vec3f a)
    {
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;
        return *this;
    }
    vec3f &operator+(vec3f const&b)
    {
        return *this += b;
    }
};

using Vector = vec3f;