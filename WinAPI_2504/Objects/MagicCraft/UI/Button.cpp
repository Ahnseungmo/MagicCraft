#include "Framework.h"

Button::Button()
{
}

Button::Button(wstring path)
{
	SetImage(path);
}
Button::~Button()
{
	delete image;
}

void Button::SetImage(wstring path) {
	image = new Quad(path);
	RectCollider::SetSize(image->GetSize());
	image->SetParent(this);
	image->UpdateWorld();
}



void Button::Update()
{
	if (!isActive) return;
	if (Input::Get()->IsKeyUp(VK_LBUTTON)) {
		if (IsPointCollision(mousePos)) {
			if (OnClick) OnClick;
		}
	}
	UpdateWorld();
	image->UpdateWorld();
}

void Button::Render()
{
	if (!isActive) return;
	/*
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	*/
	if(image) image->Render();
	RectCollider::Render();
}
