#pragma once
#include "GameObject.h"

class Ball :
    public GameObject
{
public:
    GameObject* player{ nullptr };
    Vector2 direction{-1, 0};

    void Update(double deltaTime) override;
};

