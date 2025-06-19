#pragma once

class GameMath
{
public:
	static bool IsPointBetweenVectors(const Vector2& origin,
		const Vector2& leftPoint, const Vector2& rightPoint, const Vector2& testPoint);

	static int Random(const int& min, const int& max);
	static float Random(const float& min, const float& max);

	template<typename T>
	static T Lerp(const T& start, const T& end, float factor)
	{
		return start + (end - start) * factor;
	}

	static float AngleLerp(float a, float b, float t)
	{
		float delta = fmodf(b - a + XM_PI, XM_2PI) - XM_PI;
		return a + delta * t;
	}

	template <typename T>
	static T Clamp(const T& value, const T& min, const T& max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
};