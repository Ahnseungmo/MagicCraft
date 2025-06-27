#pragma once

class GameMap : public Transform {

public:
	GameMap();
	~GameMap();

	void Update();
	void Render();

private:
	int size = tileCount.x * tileCount.y;
	Vector2 tileCount = { 200,150 };
	Vector2 tileSize = { 16,16 };

	vector<Tile*> tiles;
	Quad* quad;

	vector<InstanceData> instances;
	VertexBuffer* instanceBuffer;
};