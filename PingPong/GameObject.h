#pragma once
#include "framework.h"

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
};

class GameObject
{
public:
    Vector2 position;
    SIZE scale{};
    double speed{ 300 };
    RECT rect{};

    void UpdateRect()
    {
        rect = RECT
        {
            static_cast<LONG>(position.x - (scale.cx * 0.5f)),
            static_cast<LONG>(position.y - (scale.cy * 0.5f)),
            static_cast<LONG>(position.x + (scale.cx * 0.5f)),
            static_cast<LONG>(position.y + (scale.cy * 0.5f))
        };
    }

    virtual void Update(double deltaTime) = 0;
};

