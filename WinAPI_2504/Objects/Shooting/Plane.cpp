#include "Framework.h"

Plane::Plane()
{
    localPosition = CENTER;

    Init();

    collider = new CircleCollider();
    //collider = new RectCollider({50, 50});
    collider->SetParent(this);
}

Plane::~Plane()
{
    delete collider;
}

void Plane::Update()
{
    //collider->SetPos(pos);

    if (collider->IsPointCollision(mousePos))
    {
        collider->SetColor(1, 0, 0);
    }
    else
    {
        collider->SetColor(0, 1, 0);
    }

    ControlKeyboard();
    ControlMouse();

    UpdateWorld();

    collider->UpdateWorld();
}

void Plane::Render()
{
    GameObject::Render();
    collider->Render();
}

void Plane::ControlKeyboard()
{
    if (Input::Get()->IsKeyPress('D'))
    {
        //pos.x += SPEED * DELTA;
        //Translate(Vector2::Right() * SPEED * DELTA);
        localRotation.z -= DELTA;
    }

    if (Input::Get()->IsKeyPress('A'))
    {
        //pos.x -= SPEED * DELTA;
        //Translate(Vector2::Left() * SPEED * DELTA);
        localRotation.z += DELTA;
    }

    if (Input::Get()->IsKeyPress('W'))
    {
        //Vector2 dir(cos(rot.z + PI / 2), sin(rot.z + PI / 2));

        //pos.y += SPEED * DELTA;
        Translate(GetRight() * SPEED * DELTA);
    }
    if (Input::Get()->IsKeyPress('S'))
    {
        //pos.y -= SPEED * DELTA;
        Translate(Vector2::Down() * SPEED * DELTA);
    }

    if (Input::Get()->IsKeyPress('L'))
    {
        localScale.x += DELTA;
    }
    if (Input::Get()->IsKeyPress('J'))
    {
        localScale.x -= DELTA;
    }
    if (Input::Get()->IsKeyPress('I'))
    {
        localScale.y += DELTA;
    }
    if (Input::Get()->IsKeyPress('K'))
    {
        localScale.y -= DELTA;
    }

    if (Input::Get()->IsKeyPress(VK_UP))
    {
        localRotation.z += DELTA;
    }
    if (Input::Get()->IsKeyPress(VK_DOWN))
    {
        localRotation.z -= DELTA;
    }

    //matWorld._11 = scale.x;
    //matWorld._22 = scale.y;

    //matWorld._11 = cos(angle);
    //matWorld._12 = sin(angle);
    //matWorld._21 = -sin(angle);
    //matWorld._22 = cos(angle);

    //if (Input::Get()->IsKeyDown('1'))
    //    colorBuffer->Set(1, 0, 0);
    //
    //if (Input::Get()->IsKeyDown('2'))
    //    colorBuffer->Set(0, 1, 0);
    //
    //if (Input::Get()->IsKeyDown('3'))
    //    colorBuffer->Set(0, 0, 1);
}

void Plane::ControlMouse()
{
    Vector2 dir = mousePos - localPosition;//비행기에서 마우스로 향하는 방향
    Vector2 right = GetRight();

    float cross = Vector2::Cross(right, dir);

    if (cross < 0)
        localRotation.z -= DELTA;
    else if (cross > 0)
        localRotation.z += DELTA;

    //float destAngle = atan2(dir.y, dir.x);
    //if (rot.z < destAngle)
    //    rot.z += DELTA;
    //else if (rot.z > destAngle)
    //    rot.z -= DELTA;
}

void Plane::MakeMesh()
{
    //vertices.emplace_back(50, 0, 1, 0, 0);
    //vertices.emplace_back(-20, 0, 1, 1, 0);
    //vertices.emplace_back(-50, +50, 0, 1, 0);
    //vertices.emplace_back(-50, -50, 0, 1, 0);

    //indices = { 0, 1, 2, 1, 0, 3};
}
