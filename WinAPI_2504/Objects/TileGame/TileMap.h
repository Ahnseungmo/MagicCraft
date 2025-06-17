#pragma once

class TileMap : public Transform
{
public:
	TileMap(string file);
	~TileMap();
	
	void Render();
	
	void UpdateWorld();

	void PushCollision(RectCollider* tank);	

	void MakeNodes(vector<Node*>& nodes);

	Vector2 GetTileSize() const { return tileSize; }
	int GetCols() const { return cols; }

private:
	void LoadTiles(string file);
	void CreateTiles();

private:
	int cols = 0;
	int rows = 0;
	Vector2 tileSize;
	Vector2 imageSize;

	vector<Quad*> bgTiles;
	vector<GameTile*> objTiles;
};