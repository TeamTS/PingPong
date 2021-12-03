#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Ball.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Update(float deltatime)
{
    player->UpdateRect();
    ball->UpdateRect();

    player->Update(deltatime);
    ball->Update(deltatime);
}

void GameScene::Render(HWND hwnd, HDC hdc)
{
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    Rectangle(hdc, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom);


    RECT& rt = player->rect;
    Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);

    rt = ball->rect;
    Ellipse(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

void GameScene::Initialize(void)
{
	player = std::make_shared<Player>();
	ball = std::make_unique<Ball>();

    player->position = { 60, WINCY / 2 };
    player->scale = { 80, 180 };

    ball->position = { WINCX / 2, WINCY / 2 };
    ball->scale = { 100, 100 };
    ball->speed = 250;

    ball->player = player;
}
