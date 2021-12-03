#include "pch.h"
#include "LobbyScene.h"
#include "Button.h"

LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Update(float deltatime)
{
	button->UpdateRect();

	button->Update(deltatime);
}

void LobbyScene::Render(HWND hwnd, HDC hdc)
{
	RECT& rt = button->rect;
	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

void LobbyScene::Initialize(void)
{
}
