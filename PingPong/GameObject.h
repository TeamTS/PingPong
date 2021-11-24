#pragma once
#include "framework.h"
#include "Vector2.h"

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

