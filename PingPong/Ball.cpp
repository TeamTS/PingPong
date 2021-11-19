#include "Ball.h"

void Ball::Update(double deltaTime)
{
	RECT collideRect;
	if (IntersectRect(&collideRect, &player->rect, &rect))
	{
		// direction�� ���� ���� ��ġ�� ��¦ ��������� �ϴµ�, �ϴ� �̱��̱� ������ x�� +�θ� �÷��ݴϴ�.
		position.x += collideRect.right - collideRect.left;
		direction.x *= -1;
	}

	// TODO : 1280�� WINCX�� ���ξ� �մϴ�.
	if (position.x > 1280 - (scale.cx / 2))
	{
		direction.x *= -1;
	}

	position += direction * (speed * deltaTime);
}
