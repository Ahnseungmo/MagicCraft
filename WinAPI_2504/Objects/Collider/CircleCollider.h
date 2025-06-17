#pragma once

class CircleCollider : public Collider
{
private:
	const UINT VERTEX_SIZE = 64;

public:
	CircleCollider(float radius = 100.0f);
	~CircleCollider();

	bool IsPointCollision(const Vector2& point) override;
	bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
	bool IsCircleCollision(CircleCollider* circle) override;

	float Radius() { return radius * max(localScale.x, localScale.y); }

private:
	void MakeMesh() override;
private:
	float radius;	
};