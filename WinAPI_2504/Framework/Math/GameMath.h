#pragma once

class GameMath
{
public:
	static bool IsPointBetweenVectors(const Vector2& origin,
		const Vector2& leftPoint, const Vector2& rightPoint, const Vector2& testPoint);

	static int Random(const int& min, const int& max);
	static float Random(const float& min, const float& max);
};