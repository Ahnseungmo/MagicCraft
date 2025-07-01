#pragma once

class GameMap : public Transform {


public:
	struct TileData {
		Tile::State state = Tile::FLOOR;
		Tile* object = nullptr;
	};


	GameMap(Vector2 count);
	~GameMap();

	void Update();
	void Render();
	void Edit();

	void SetInstanceBuffer(vector<Tile*> tiles, vector<InstanceData> instances, VertexBuffer*& buffer);

//	void SetInsanceBuffer(vector<Tile*&>& tiles, vector<InstanceData&>& instances, VertexBuffer*& buffer);

//	void SetInsanceBuffer(VertexBuffer*& buffer);

	void MapGenerate();
	int NeighTileData(int index);

	Vector2 CalTilePos(int index);
	int CalTilePos(Vector2 pos);


private:

	vector<TileData*> tileDatas;

	vector<Tile*> floors;
	vector<Tile*> objects;

	Vector2 tileSize = { 32,32 };
	Vector2 tileCount;
	

	Quad* quad;

	vector<InstanceData> floorInstances;
	VertexBuffer* floorInstanceBuffer;


	vector<InstanceData> objectInstances;
	VertexBuffer* objectInstanceBuffer;


};