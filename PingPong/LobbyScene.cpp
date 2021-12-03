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

	switch (inputStage)
	{
	case LobbyInputStage::IP:
		ip = L"■ IP : ";
		port = L"PORT : ";
		break;
	case LobbyInputStage::PORT:
		ip = L"IP : ";
		port = L"■ PORT : ";
		break;
	case LobbyInputStage::END:
		portValue = std::stoi(portInput);
		ip = L"IP : ";
		port = L"PORT : ";
		break;
	default:
		break;
	}
}

void LobbyScene::Render(HWND hwnd, HDC hdc)
{
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	Rectangle(hdc, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom);

	RECT& rt = button->rect;

	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
	DrawText(hdc, button->str, _tcslen(button->str), &rt, DT_CENTER | DT_VCENTER);

	std::wstring text;
	text = (isServerConnected ? L"서버연결됨" : L"서버연결안됨");
		
	swprintf_s(str, text.c_str());

	TextOut(hdc, 0, 0, str, _tcslen(str));

	ip += ipInput;
	port += portInput;

	TextOut(hdc, 0, 300, ip.c_str(), ip.size());
	TextOut(hdc, 0, 320, port.c_str(), port.size());
}

void LobbyScene::Initialize(void)
{
	button->scale = { 100,50 };
	button->position = { WINCX / 2, WINCY / 2 };
	swprintf_s(button->str, L"서버연결시도");
}