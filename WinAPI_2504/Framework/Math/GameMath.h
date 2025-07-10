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

    template<typename T>
    static T TrilinearInterpolation(T*** data, float x, float y, float z, int size_x, int size_y, int size_z)
    {
        // 1. 좌표를 그리드 경계 내로 클램핑 (선택 사항이지만 안전을 위해 권장)
        // -1.0001f는 정수 인덱스 + 소수 부분을 고려하여 마지막 인덱스를 넘어가지 않게 합니다.
        x = max(0.0f, min((float)size_x - 1.0001f, x));
        y = max(0.0f, min((float)size_y - 1.0001f, y));
        z = max(0.0f, min((float)size_z - 1.0001f, z));

        // 2. 주변 8개 점의 정수 좌표 (큐브의 꼭짓점) 추출
        int x0 = static_cast<int>(floor(x)); // 현재 좌표보다 작거나 같은 가장 큰 정수
        int y0 = static_cast<int>(floor(y));
        int z0 = static_cast<int>(floor(z));

        int x1 = x0 + 1; // 다음 정수 좌표
        int y1 = y0 + 1;
        int z1 = z0 + 1;

        // 3. 각 축의 보간 비율 (소수 부분) 계산
        // 이 값들은 0.0에서 1.0 사이의 값을 가집니다.
        float fx = x - x0;
        float fy = y - y0;
        float fz = z - z0;

        // 4. X축 방향으로 4번의 선형 보간 (X축을 따라 큐브의 4개 엣지에서 보간)
        // z0 평면 (아래쪽 평면)
        T c00 = Lerp(data[z0][y0][x0], data[z0][y0][x1], fx); // (x, y0, z0) 위치의 값
        T c01 = Lerp(data[z0][y1][x0], data[z0][y1][x1], fx); // (x, y1, z0) 위치의 값

        // z1 평면 (위쪽 평면)
        T c10 = Lerp(data[z1][y0][x0], data[z1][y0][x1], fx); // (x, y0, z1) 위치의 값
        T c11 = Lerp(data[z1][y1][x0], data[z1][y1][x1], fx); // (x, y1, z1) 위치의 값

        // 5. Y축 방향으로 2번의 선형 보간 (X축 보간 결과에서 Y축을 따라 큐브의 2개 면에서 보간)
        T c0 = Lerp(c00, c01, fy); // (x, y, z0) 위치의 값
        T c1 = Lerp(c10, c11, fy); // (x, y, z1) 위치의 값

        // 6. Z축 방향으로 1번의 선형 보간 (최종적으로 큐브 내부의 (x,y,z) 위치 값 추정)
        T result = Lerp(c0, c1, fz);

        return result;
    }
};