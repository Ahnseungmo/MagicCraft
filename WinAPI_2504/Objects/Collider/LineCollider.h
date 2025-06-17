#pragma once

class LineCollider : public Collider
{
public:
	LineCollider(Vector2 startPos, Vector2 endPos);

	bool IsPointCollision(const Vector2& point) override;
	bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
	bool IsCircleCollision(CircleCollider* circle) override;

	Vector2 Start() { return startPos * world; }
	Vector2 End() { return endPos * world; }

private:
	void MakeMesh() override;

private:
	Vector2 startPos, endPos;
};