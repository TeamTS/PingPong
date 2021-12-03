#pragma once
class Scene
{
public:
	virtual void Initialize(void) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Render(HWND hwnd, HDC hdc) = 0;
};

