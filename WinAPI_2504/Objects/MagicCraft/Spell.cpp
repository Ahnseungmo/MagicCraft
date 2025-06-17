#include "Framework.h"

Spell::Spell()
{
	image = new Quad(L"Resources/Textures/MagicCraft/SampleSpell.png");
	image->SetParent(this);
	image->UpdateWorld();

	
}

Spell::~Spell()
{
	delete image;
}

void Spell::Update()
{
	if (!isActive) return;

	Translate(direction * speed * DELTA);
	UpdateWorld();
	image->UpdateWorld();
}

void Spell::Render()
{
	image->Render();
	RectCollider::Render();

}

void Spell::Spawn(Vector2 pos,Vector2 dir,Vector2 size)
{
	SetSize(size);
	localRotation.z = atan2f(dir.y,dir.x);
	direction = dir;
	SetLocalPosition(pos);

	isActive = true;
}