#include "Framework.h"

Camera::Camera()
{
	tag = "Camera";

	viewBuffer = new MatrixBuffer();
}

Camera::~Camera()
{
	delete viewBuffer;
}

void Camera::Update()
{
    if (target)
        FollowMode();
    else
	    FreeMode();

	UpdateWorld();	

	view = XMMatrixInverse(nullptr, world);
	viewBuffer->Set(view);
	viewBuffer->SetVS(1);
}

void Camera::FreeMode()
{
    if (Input::Get()->IsKeyPress(VK_RBUTTON))
    {
        if (Input::Get()->IsKeyPress('W'))
            Translate(Vector2::Up() * speed * DELTA);
        if (Input::Get()->IsKeyPress('S'))
            Translate(Vector2::Down() * speed * DELTA);
        if (Input::Get()->IsKeyPress('A'))
            Translate(Vector2::Left() * speed * DELTA);
        if (Input::Get()->IsKeyPress('D'))
            Translate(Vector2::Right() * speed * DELTA);
    }
}

void Camera::FollowMode()
{

}
