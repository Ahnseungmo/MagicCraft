#pragma once

class Collider : public GameObject
{
protected:
	enum class Type
	{
		Rect, Circle, Line
	};

public:
	Collider();
	~Collider() = default;

	bool IsCollision(Collider* collider, Vector2* overlap = nullptr);

	virtual bool IsPointCollision(const Vector2& point) = 0;
	virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
	virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

	void Render() override;

	virtual void MakeMesh() override;

	static void SwitchDraw() { isDraw = !isDraw; }

protected:
	Type type;

private:
	static bool isDraw;
};