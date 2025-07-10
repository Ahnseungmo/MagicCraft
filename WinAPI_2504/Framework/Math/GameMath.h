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
        // 1. ��ǥ�� �׸��� ��� ���� Ŭ���� (���� ���������� ������ ���� ����)
        // -1.0001f�� ���� �ε��� + �Ҽ� �κ��� ����Ͽ� ������ �ε����� �Ѿ�� �ʰ� �մϴ�.
        x = max(0.0f, min((float)size_x - 1.0001f, x));
        y = max(0.0f, min((float)size_y - 1.0001f, y));
        z = max(0.0f, min((float)size_z - 1.0001f, z));

        // 2. �ֺ� 8�� ���� ���� ��ǥ (ť���� ������) ����
        int x0 = static_cast<int>(floor(x)); // ���� ��ǥ���� �۰ų� ���� ���� ū ����
        int y0 = static_cast<int>(floor(y));
        int z0 = static_cast<int>(floor(z));

        int x1 = x0 + 1; // ���� ���� ��ǥ
        int y1 = y0 + 1;
        int z1 = z0 + 1;

        // 3. �� ���� ���� ���� (�Ҽ� �κ�) ���
        // �� ������ 0.0���� 1.0 ������ ���� �����ϴ�.
        float fx = x - x0;
        float fy = y - y0;
        float fz = z - z0;

        // 4. X�� �������� 4���� ���� ���� (X���� ���� ť���� 4�� �������� ����)
        // z0 ��� (�Ʒ��� ���)
        T c00 = Lerp(data[z0][y0][x0], data[z0][y0][x1], fx); // (x, y0, z0) ��ġ�� ��
        T c01 = Lerp(data[z0][y1][x0], data[z0][y1][x1], fx); // (x, y1, z0) ��ġ�� ��

        // z1 ��� (���� ���)
        T c10 = Lerp(data[z1][y0][x0], data[z1][y0][x1], fx); // (x, y0, z1) ��ġ�� ��
        T c11 = Lerp(data[z1][y1][x0], data[z1][y1][x1], fx); // (x, y1, z1) ��ġ�� ��

        // 5. Y�� �������� 2���� ���� ���� (X�� ���� ������� Y���� ���� ť���� 2�� �鿡�� ����)
        T c0 = Lerp(c00, c01, fy); // (x, y, z0) ��ġ�� ��
        T c1 = Lerp(c10, c11, fy); // (x, y, z1) ��ġ�� ��

        // 6. Z�� �������� 1���� ���� ���� (���������� ť�� ������ (x,y,z) ��ġ �� ����)
        T result = Lerp(c0, c1, fz);

        return result;
    }
};