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

	if (IsPointCollision(mousePos)) {
		if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
			clickCheck = true;
		}
		if (clickCheck) {
			if (Input::Get()->IsKeyUp(VK_LBUTTON)) {
				clickCheck = false;
				if (OnClick) OnClick;
				if (OnClickInt) OnClickInt(intParameter);
			}

		}

	}
	else clickCheck = false;

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
