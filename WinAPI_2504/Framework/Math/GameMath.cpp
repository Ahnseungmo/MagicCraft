#include "Framework.h"

bool GameMath::IsPointBetweenVectors(const Vector2& origin, const Vector2& leftPoint, const Vector2& rightPoint, const Vector2& testPoint)
{
	Vector2 leftDir = leftPoint - origin;
	Vector2 rightDir = rightPoint - origin;

	Vector2 pointDir = testPoint - origin;

	float crossLeft = Vector2::Cross(pointDir, leftDir);
	float crossRight = Vector2::Cross(pointDir, rightDir);

	return crossLeft * crossRight < 0;
}

int GameMath::Random(const int& min, const int& max)
{
	return rand() % (max - min) + min;
}

float GameMath::Random(const float& min, const float& max)
{
	float normal = rand() / (float)RAND_MAX; // 0.0f ~ 1.0f

	return min + (max - min) * normal;
}
