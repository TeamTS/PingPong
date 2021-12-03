#pragma once
#include "GameObject.h"
class Button :
	public GameObject
{
public:
	// 버튼
	// 눌렸는지 확인
	// 눌린 뒤 어떤 함수를 실행시키고 싶다면?
	[[nodiscard]] bool IsClicked(HWND hwnd);

	// GameObject을(를) 통해 상속됨
	virtual void Update(double deltaTime) override;
};

