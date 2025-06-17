#pragma once

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 pos;
		Vector2 axis[2];
		Vector2 halfSize;
	};

public:
	RectCollider(Vector2 size = Vector2(50, 50));
	~RectCollider() = default;
	
	bool IsPointCollision(const Vector2& point) override;
	bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
	bool IsCircleCollision(CircleCollider* circle) override;	

	Vector2 LeftTop();
	Vector2 LeftBottom();
	Vector2 RightTop();
	Vector2 RightBottom();

	float Left();
	float Right();
	float Top();
	float Bottom();

	ObbDesc GetObb();

	void SetSize(Vector2 size);

	Vector2 Size() { return size * GetGlobalScale(); }
	Vector2 Half() { return Size() * 0.5f; }

private:
	void MakeMesh() override;

	bool IsAABB(RectCollider* rect, Vector2* overlap);
	bool IsOBB(RectCollider* rect);

	bool IsSeperateAxis(const Vector2& seperateAxis,
		const ObbDesc& box1, const ObbDesc& box2);

private:
	ObbDesc obbDesc;

	Vector2 size;
};