#include "Framework.h"

bool Collider::isDraw = true;

Collider::Collider() : GameObject(L"Collider.hlsl")
{    
    SetColor(0, 1, 0);
}

bool Collider::IsCollision(Collider* collider, Vector2* overlap)
{
    if (!IsActive()) return false;
    if (!collider->IsActive()) return false;

    switch (collider->type)
    {
    case Collider::Type::Rect:
        return IsRectCollision((RectCollider*)collider, overlap);
    case Collider::Type::Circle:
        return IsCircleCollision((CircleCollider*)collider);    
    }

    return false;
}

void Collider::Render()
{
	if (!isDraw) return;
    if (!isActive) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);    

    material->Set();

    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

void Collider::MakeMesh()
{
}
