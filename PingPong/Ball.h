#pragma once
#include "GameObject.h"
class Ball :
    public GameObject
{
public:
    void Update(double deltaTime) override;
};

