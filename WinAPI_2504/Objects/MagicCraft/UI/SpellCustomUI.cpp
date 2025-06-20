#include "Framework.h"

SpellCustomUI::SpellCustomUI() : RectCollider({500,500})
{
	isActive = false;
	backGround = new Quad(L"Resources/Textures/MagicCraft/UI/Book.png");
	backGround->SetParent(this);

}

SpellCustomUI::~SpellCustomUI()
{
	delete backGround;
}

void SpellCustomUI::Update()
{
	if (!isActive)return;
	backGround->UpdateWorld();
}

void SpellCustomUI::Render()
{
	if (!isActive)return;
	backGround->Render();
}
