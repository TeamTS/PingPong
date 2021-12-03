#pragma once
#include "Scene.h"

class Player;
class Ball;

class GameScene :
    public Scene
{
public:
    GameScene();
    ~GameScene();

    std::shared_ptr<Player> player;
    std::unique_ptr<Ball> ball;

    // Scene��(��) ���� ��ӵ�
    virtual void Update(float deltatime) override;
    virtual void Render(HWND hwnd, HDC hdc) override;

    // Scene��(��) ���� ��ӵ�
    virtual void Initialize(void) override;
};

