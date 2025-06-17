#include "Framework.h"

EditTile::EditTile() : RectCollider(Vector2(128, 90))
{
	image = new Quad(L"Resources/Textures/Tiles/tileDirt.png");
	image->SetParent(this);
	image->SetLocalPosition(Vector2(0, 50));
}

EditTile::~EditTile()
{
}

void EditTile::UpdateWorld()
{
	RectCollider::UpdateWorld();
	image->UpdateWorld();	
}

void EditTile::Render()
{
	image->Render();
	RectCollider::Render();
}
