#include "Ball.h"

void Ball::Update(double deltaTime)
{
	RECT collideRect;
	if (IntersectRect(&collideRect, &player->rect, &rect))
	{
		// direction에 따라서 공의 위치를 살짝 보정해줘야 하는데, 일단 싱글이기 때문에 x를 +로만 늘려줍니다.
		position.x += collideRect.right - collideRect.left;
		direction.x *= -1;
	}

	// TODO : 1280을 WINCX로 감싸야 합니다.
	if (position.x > 1280 - (scale.cx / 2))
	{
		direction.x *= -1;
	}

	position += direction * (speed * deltaTime);
}
