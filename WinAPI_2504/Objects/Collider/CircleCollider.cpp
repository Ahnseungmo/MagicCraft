#include "Framework.h"

CircleCollider::CircleCollider(float radius) : radius(radius)
{
	type = Type::Circle;

	Init();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::MakeMesh()
{
	vector<Vertex>& vertices = mesh->GetVertices();

	vertices.reserve(VERTEX_SIZE + 1);

	float stepAngle = XM_2PI / VERTEX_SIZE;

	for (int i = 0; i <= VERTEX_SIZE; i++)
	{
		float x = cos(stepAngle * i) * radius;
		float y = sin(stepAngle * i) * radius;

		vertices.emplace_back(x, y);
	}
}

bool CircleCollider::IsPointCollision(const Vector2& point)
{
	float distance = (GetGlobalPosition() - point).Magnitude();

	return distance <= Radius();
}

bool CircleCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
	return rect->IsCircleCollision(this);
}

bool CircleCollider::IsCircleCollision(CircleCollider* circle)
{
	float distance = Vector2::Distance(circle->GetGlobalPosition(), GetGlobalPosition());

	return distance <= (Radius() + circle->Radius());
}
