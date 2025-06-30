#include "Framework.h"

Tile::Tile(Vector2 size) : RectCollider(size)
{


}

Tile::~Tile()
{
}

void Tile::CalTilesetPos()
{
	if (state == WALL) {
		SetTilesetPos(wallTileShapePos.at(tileType));
	
	}
	else {
		SetTilesetPos(floorTileShapePos.at(4));
	}
}
