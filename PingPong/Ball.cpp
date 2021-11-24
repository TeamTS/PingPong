#include "pch.h"
#include "Ball.h"

void Ball::CalculateThetaAndSetDirection(Vector2 position)
{
	// position = Player Position
	float yDist = this->position.y - position.y;

	// 높이 차이를 통해 세타 계산
	// TODO : 세타의 증가량은 추가로 조절 필요
	constexpr float growthRate = 0.2f;

	// 세타의 단위를 Radian으로 변경 후, 세타를 통한 단위원 속 x, y 구하기
	float rad = (yDist * growthRate) * (3.141592 / 180.0);
	float x = cos(rad);
	float y = sin(rad);

	if (x < 0)
		x *= -1;
	// 할당 후, 크기 1로 세팅
	direction = { x,y };
	direction.Normalize();
}

void Ball::WallClip(void)
{
	// TODO : 1280을 WINCX로 감싸야 합니다.
	if (position.x > 1280 - (scale.cx / 2))
	{
		direction.x *= -1;
	}

	// TODO : 1280을 WINCX로 감싸야 합니다.
	if (position.x < 0 + (scale.cx / 2))
	{
		direction.x *= -1;
	}

	// TODO : 1280을 WINCX로 감싸야 합니다.
	if (position.y > 720 - (scale.cy / 2))
	{
		direction.y *= -1;
	}

	// TODO : 1280을 WINCX로 감싸야 합니다.
	if (position.y < 0 + (scale.cy / 2))
	{
		direction.y *= -1;
	}
}

void Ball::Update(double deltaTime)
{
	RECT collideRect;
	if (IntersectRect(&collideRect, &player->rect, &rect))
	{
		position.x += collideRect.right - collideRect.left;
		CalculateThetaAndSetDirection(player->position);
	}

	WallClip();

	position += direction * (speed * deltaTime);
}
