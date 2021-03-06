#include "pch.h"
#include "Player.h"

void Player::Update(double deltaTime)
{
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        position.y -= speed * deltaTime;
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        position.y += speed * deltaTime;
    }
}