#include "Framework.h"

RectCollider::RectCollider(Vector2 size) : size(size)
{
    type = Type::Rect;

    Init();
}

//AABB
//bool RectCollider::IsPointCollision(const Vector2& point)
//{
//    if (point.x > Left() && point.x < Right())
//    {
//        if (point.y > Bottom() && point.y < Top())
//            return true;
//    }
//
//    return false;
//}

//역행렬
//bool RectCollider::IsPointCollision(const Vector2& point)
//{
//    Vector2 coord = point * XMMatrixInverse(nullptr, world);
//
//    if (abs(coord.x) < size.x * 0.5f && abs(coord.y) < size.y * 0.5f)
//        return true;
//
//    return false;
//}

//외적
bool RectCollider::IsPointCollision(const Vector2& point)
{    
    bool isLeftTop = GameMath::IsPointBetweenVectors(LeftTop(), RightTop(), LeftBottom(), point);
    bool isRightTop = GameMath::IsPointBetweenVectors(RightTop(), LeftTop(), RightBottom(), point);
    bool isRightBottom = GameMath::IsPointBetweenVectors(RightBottom(), RightTop(), LeftBottom(), point);

    return isLeftTop && isRightTop && isRightBottom;
}

bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    if (overlap)
        return IsAABB(rect, overlap);

    return IsOBB(rect);
}

bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
    ObbDesc obb = GetObb();

    Vector2 direction = obb.pos - circle->GetGlobalPosition();

    float x = abs(Vector2::Dot(direction, obb.axis[0]));
    float y = abs(Vector2::Dot(direction, obb.axis[1]));

    if (x > obb.halfSize.x + circle->Radius()) return false;
    if (y > obb.halfSize.y + circle->Radius()) return false;

    if (x < obb.halfSize.x) return true;
    if (y < obb.halfSize.y) return true;

    Vector2 temp = Vector2(x, y) - obb.halfSize;

    return circle->Radius() > temp.Magnitude();
}

Vector2 RectCollider::LeftTop()
{
    Vector2 edge = Vector2(-size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 edge = Vector2(-size.x, -size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 edge = Vector2(+size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 edge = Vector2(+size.x, -size.y) * 0.5f;

    return edge * world;
}

float RectCollider::Left()
{
    float minLeft = min(LeftTop().x, LeftBottom().x);
    float minRight = min(RightTop().x, RightBottom().x);

    return min(minLeft, minRight);
}

float RectCollider::Right()
{
    float maxLeft = max(LeftTop().x, LeftBottom().x);
    float maxRight = max(RightTop().x, RightBottom().x);

    return max(maxLeft, maxRight);
}

float RectCollider::Top()
{
    float maxTop = max(LeftTop().y, LeftBottom().y);
    float maxBottom = max(RightTop().y, RightBottom().y);

    return max(maxTop, maxBottom);
}

float RectCollider::Bottom()
{
    float minTop = min(LeftTop().y, LeftBottom().y);
    float minBottom = min(RightTop().y, RightBottom().y);

    return min(minTop, minBottom);
}

RectCollider::ObbDesc RectCollider::GetObb()
{
    obbDesc.pos = GetGlobalPosition();
    obbDesc.halfSize = Half();

    obbDesc.axis[0] = GetRight();
    obbDesc.axis[1] = GetUp();

    return obbDesc;
}

void RectCollider::SetSize(Vector2 size)
{
    this->size = size;

	Vector2 halfSize = size * 0.5f;

	vector<Vertex>& vertices = mesh->GetVertices();
	vertices.clear();

    vertices.emplace_back(-halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, +halfSize.y);

    mesh->UpdateVertices();
}

void RectCollider::MakeMesh()
{
    Vector2 halfSize = size * 0.5f;

	vector<Vertex>& vertices = mesh->GetVertices();

    vertices.emplace_back(-halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, +halfSize.y);
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    float left = max(Left(), rect->Left());
    float right = min(Right(), rect->Right());
    float bottom = max(Bottom(), rect->Bottom());
    float top = min(Top(), rect->Top());

    overlap->x = right - left;
    overlap->y = top - bottom;

    return overlap->x >= 0 && overlap->y >= 0;
}

bool RectCollider::IsOBB(RectCollider* rect)
{
    ObbDesc obbA = GetObb();
    ObbDesc obbB = rect->GetObb();

    if (IsSeperateAxis(obbA.axis[0], obbA, obbB)) return false;
    if (IsSeperateAxis(obbA.axis[1], obbA, obbB)) return false;
    if (IsSeperateAxis(obbB.axis[0], obbA, obbB)) return false;
    if (IsSeperateAxis(obbB.axis[1], obbA, obbB)) return false;

    return true;
}

bool RectCollider::IsSeperateAxis(const Vector2& seperateAxis, const ObbDesc& box1, const ObbDesc& box2)
{
    float d = abs(Vector2::Dot(seperateAxis, box1.pos - box2.pos));

    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float a = abs(Vector2::Dot(seperateAxis, right)) + abs(Vector2::Dot(seperateAxis, up));

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float b = abs(Vector2::Dot(seperateAxis, right)) + abs(Vector2::Dot(seperateAxis, up));

    return d > (a + b);
}
