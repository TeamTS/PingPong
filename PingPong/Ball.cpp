#include "Ball.h"

void Ball::CalculateThetaAndSetDirection(Vector2 position)
{
	// position = Player Position
	float yDist = this->position.y - position.y;

	// ���� ���̸� ���� ��Ÿ ���
	// TODO : ��Ÿ�� �������� �߰��� ���� �ʿ�
	constexpr float growthRate = 0.2f;

	// ��Ÿ�� ������ Radian���� ���� ��, ��Ÿ�� ���� ������ �� x, y ���ϱ�
	float rad = (yDist * growthRate) * (3.141592 / 180.0);
	float x = cos(rad);
	float y = sin(rad);

	if (x < 0)
		x *= -1;
	// �Ҵ� ��, ũ�� 1�� ����
	direction = { x,y };
	direction.Normalize();
}

void Ball::Update(double deltaTime)
{
	RECT collideRect;
	if (IntersectRect(&collideRect, &player->rect, &rect))
	{
		position.x += collideRect.right - collideRect.left;
		CalculateThetaAndSetDirection(player->position);
	}

	// TODO : 1280�� WINCX�� ���ξ� �մϴ�.
	if (position.x > 1280 - (scale.cx / 2))
	{
		direction.x *= -1;
	}

	position += direction * (speed * deltaTime);
}
