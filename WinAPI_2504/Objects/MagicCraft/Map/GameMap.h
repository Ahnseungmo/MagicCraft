#pragma once

class GameMap : public Transform {


public:
	struct TileData {
		Tile::State state = Tile::FLOOR;
		Tile* object = nullptr;
		int biome = 0;
		float biomeXSize = 6;
		vector<Vector2> biomePos = {
			{biomeXSize * 0,0},//Normal
			{biomeXSize * 1,0},//deep forest
			{biomeXSize * 2,0},//fall
			{biomeXSize * 3,0},//sahara
			{biomeXSize * 4,0} //snow
		};
	};


	GameMap(Vector2 count);
	~GameMap();

	void Update();
	void Render();
	void Edit();

	void SetInstanceBuffer(vector<Tile*> tiles, vector<InstanceData>& instances, VertexBuffer*& buffer);

	void SetInstanceBuffers();
	//	void SetInsanceBuffer(vector<Tile*&>& tiles, vector<InstanceData&>& instances, VertexBuffer*& buffer);

	//	void SetInsanceBuffer(VertexBuffer*& buffer);

	void MapGenerate();
	int NeighTileData(int index);

	Vector2 CalTilePos(int index);
	int CalTilePos(Vector2 pos);

	void MakeNodes(vector<Node*>& nodes);

	Vector2 GetPlayerSpawnPoint() { return playerSpawnPoint; }
	Vector2 GetTileCount() { return tileCount; }

	Vector2 CalPosToTilePos(Vector2 pos) {
//		Vector2 tilebo = Vector2(tileSize.x / 2, tileSize.y / 2);
		return (pos )/tileSize;
	}

	int CalPosToIndex(Vector2 pos) {
		Vector2 cal = CalPosToTilePos(pos);
//		int index = (tileCount.y-1-cal.y) * tileCount.y + cal.x;
		int index = (tileCount.y - 1 - (int)cal.y) * tileCount.x + (int)cal.x;  // y축 반전을 고려
		return index;
	}

	int CalTilePosToIndex(Vector2 pos) {
		Vector2 cal = pos;
		int index = (tileCount.y - 1 - (int)cal.y) * tileCount.x + (int)cal.x;  // y축 반전을 고려
		return index;
	}

	TileData*& GetTileData(int index) {return tileDatas.at(index); }

	vector<Vector2> GetBiomeBassTilePos() { return biomeBassTilePos; }
	vector<Tile*>& GetFloors() { return floors; }

	vector<Vector2>& GetEnemySpanwer() { return enemySpawner; }

private:

	vector<TileData*> tileDatas;

	vector<Tile*> floors;
	vector<Tile*> objects;

	Vector2 tileSize = { 32,32 };
	Vector2 tileCount;
	
	Vector2 playerSpawnPoint = {0,0};
	vector<Vector2> enemySpawner;


	vector<Vector2> biomeBassTilePos;

	Quad* quad;

	vector<InstanceData> floorInstances;
	VertexBuffer* floorInstanceBuffer;


	vector<InstanceData> objectInstances;
	VertexBuffer* objectInstanceBuffer;

	MapGenerator* mapGenerator;
};