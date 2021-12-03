#pragma once
#include "Scene.h"
class Button;
class LobbyScene :
	public Scene
{
public:
	std::shared_ptr<Button> button;
	LobbyScene();
	~LobbyScene();
	// Scene��(��) ���� ��ӵ�
	virtual void Update(float deltatime) override;
	virtual void Render(HWND hwnd, HDC hdc) override;

	TCHAR str[100] = L"";
	bool isServerConnected = false;

	TCHAR ip_str[100] = L"";
	TCHAR port_str[100] = L"";

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
};

