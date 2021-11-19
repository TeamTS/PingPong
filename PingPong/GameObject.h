#pragma once
#include "framework.h"

struct Position
{
    float x = 0;
    float y = 0;
};

class GameObject
{
public:

    Position position;
    SIZE scale{};
    double speed{ 150 };
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

