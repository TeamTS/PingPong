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
	DrawText(hdc, button->str, _tcslen(button->str), &rt, DT_CENTER | DT_VCENTER);
}

void LobbyScene::Initialize(void)
{
	button->scale = { 100,50 };
	button->position = { WINCX / 2, WINCY / 2 };
	swprintf_s(button->str, L"서버연결시도");
}
