#pragma once
#include <cmath>

struct Vector2
{
    float x = 0;
    float y = 0;
    Vector2 operator+=(Vector2 vec)
    {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    Vector2 operator*(double d)
    {
        Vector2 result = *this;
        result.x *= d;
        result.y *= d;
        return result;
    }

    FORCEINLINE void Normalize(void);
};

void Vector2::Normalize(void)
{
    float size = sqrt((x * x) + (y * y));
    x = x / size;
    y = y / size;
}