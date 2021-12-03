#include "pch.h"
#include "Button.h"

bool Button::IsClicked(HWND hwnd)
{
	// rect 안에 마우스가 들어왔다면
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
