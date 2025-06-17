#include "Framework.h"

TileMap::TileMap(string file)
{
	LoadTiles(file);
}

TileMap::~TileMap()
{
	for (Quad* tile : bgTiles)
	{
		delete tile;
	}
	bgTiles.clear();
}

void TileMap::Render()
{
	for (Quad* tile : bgTiles)
	{
		tile->Render();
	}

	for (GameTile* tile : objTiles)
	{
		tile->Render();
	}
}

void TileMap::UpdateWorld()
{
	Transform::UpdateWorld();

	for (Quad* tile : bgTiles)
	{
		tile->UpdateWorld();
	}

	for (GameTile* tile : objTiles)
	{
		tile->UpdateWorld();
	}
}

void TileMap::PushCollision(RectCollider* tank)
{
	Vector2 overlap;

	Vector2 pos = tank->GetGlobalPosition();

	for (GameTile* tile : objTiles)
	{		
		if (tile->IsRectCollision(tank, &overlap))
		{			
			if (overlap.x > overlap.y)
			{
				if (pos.y < tile->GetGlobalPosition().y)
					tank->Translate(Vector2::Down() * overlap.y);
				else
					tank->Translate(Vector2::Up() * overlap.y);
			}
			else
			{
				if (pos.x < tile->GetGlobalPosition().x)
					tank->Translate(Vector2::Left() * overlap.x);
				else
					tank->Translate(Vector2::Right() * overlap.x);
			}
		}
	}
}

void TileMap::MakeNodes(vector<Node*>& nodes)
{
	for (Quad* tile : bgTiles)
	{
		//Vector2 tilePos = tile->GetGlobalPosition() + Vector2::Up() * tileSize.y * 0.25f;
		Vector2 tilePos = tile->GetGlobalPosition();
		Node* node = new Node(tilePos, nodes.size());

		for (GameTile* obj : objTiles)
		{
			if (obj->IsPointCollision(tilePos))
			{
				node->SetState(Node::Obstacle);
			}
		}

		nodes.push_back(node);
	}
}

void TileMap::LoadTiles(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	if (reader->IsFailed())
	{
		delete reader;
		return;
	}

	cols = reader->Int();
	rows = reader->Int();

	tileSize = reader->Vector();
	imageSize = reader->Vector();

	CreateTiles();

	for (Quad* tile : bgTiles)
	{
		wstring textureFile = reader->WString();
		tile->GetMaterial()->SetBaseMap(textureFile);
	}

	int objTileCount = reader->Int();
	Vector2 startPos = Vector2(imageSize.x * 0.5f, SCREEN_HEIGHT - imageSize.y * 0.5f);

	for (int i = 0; i < objTileCount; i++)
	{
		Vector2 pos = reader->Vector();
		wstring file = reader->WString();
		GameTile* objTile = new GameTile(file, tileSize);		
		objTile->SetLocalPosition(pos - startPos);
		objTile->UpdateWorld();
		objTile->SetParent(this);

		objTiles.push_back(objTile);
	}

	delete reader;
}

void TileMap::CreateTiles()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			Quad* tile = new Quad(imageSize);
			tile->SetLocalPosition(Vector2(x * tileSize.x, -y * tileSize.y));
			tile->UpdateWorld();
			tile->SetParent(this);

			bgTiles.push_back(tile);
		}
	}
}
