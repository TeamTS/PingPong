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

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
};

