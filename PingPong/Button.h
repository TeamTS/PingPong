#pragma once
#include "GameObject.h"
class Button :
	public GameObject
{
public:
	// ��ư
	// ���ȴ��� Ȯ��
	// ���� �� � �Լ��� �����Ű�� �ʹٸ�?
	[[nodiscard]] bool IsClicked(HWND hwnd);

	// GameObject��(��) ���� ��ӵ�
	virtual void Update(double deltaTime) override;
};

