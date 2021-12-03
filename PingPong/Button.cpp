#include "pch.h"
#include "Button.h"

bool Button::IsClicked(HWND hwnd)
{
	// rect �ȿ� ���콺�� ���Դٸ�
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);

	if (PtInRect(&rect, pt))
		return true;
	return false;
}

void Button::Update(double deltaTime)
{
	
}
