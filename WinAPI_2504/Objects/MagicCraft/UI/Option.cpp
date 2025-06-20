#include "Framework.h"

Option::Option() : RectCollider({ 60,60 })
{
}

Option::Option(Option* option) : RectCollider({ 60, 60 })
{
	image = new Quad(option->image->GetMaterial()->GetBaseMap()->GetFile());
	image->SetParent(this);
	spellEvent = option->spellEvent;
	UpdateWorld();
}

Option::~Option()
{
	delete image;
}

void Option::Update()
{
	UpdateWorld();
	image->UpdateWorld();
}

void Option::Render()
{
	RectCollider::Render();
	image->Render();
}

