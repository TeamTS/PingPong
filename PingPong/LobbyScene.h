#pragma once
#include "Scene.h"
class Button;
enum class LobbyInputStage {IP, PORT, END};

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

	TCHAR str[100] = L"";
	bool isServerConnected = false;

	LobbyInputStage inputStage = LobbyInputStage::IP;
	std::wstring ip = L"IP : ";
	std::wstring ipInput = L"";
	std::wstring port = L"PORT : ";
	std::wstring portInput = L"";
	unsigned short portValue = 0;
	// Scene을(를) 통해 상속됨
	virtual void Initialize(void) override;
};

