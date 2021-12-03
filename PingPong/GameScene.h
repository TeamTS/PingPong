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

    // Scene을(를) 통해 상속됨
    virtual void Update(float deltatime) override;
    virtual void Render(HWND hwnd, HDC hdc) override;

    // Scene을(를) 통해 상속됨
    virtual void Initialize(void) override;
};

