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
	// Scene을(를) 통해 상속됨
	virtual void Update(float deltatime) override;
	virtual void Render(HWND hwnd, HDC hdc) override;

	// Scene을(를) 통해 상속됨
	virtual void Initialize(void) override;
};

