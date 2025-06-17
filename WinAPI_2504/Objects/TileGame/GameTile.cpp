#include "Framework.h"

GameTile::GameTile(wstring textureFile, Vector2 size)
	: RectCollider(size)	
{
	image = new Quad(textureFile);
	image->SetParent(this);	
	image->SetLocalPosition(Vector2(0, 50));
}

GameTile::~GameTile()
{
	delete image;
}

void GameTile::Render()
{
	image->Render();
	RectCollider::Render();
}

void GameTile::UpdateWorld()
{
	RectCollider::UpdateWorld();
	image->UpdateWorld();
}
