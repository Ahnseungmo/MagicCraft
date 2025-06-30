#pragma once

class GameMap : public Transform {


public:
	enum WallShapeID {
		WALL_NONE = 0,
		WALL_TOP = 1,
		WALL_BOTTOM = 2,
		WALL_LEFT = 3,
		WALL_RIGHT = 4,
		WALL_VERTICAL = 5,     // 상하
		WALL_HORIZONTAL = 6,   // 좌우
		WALL_CROSS = 7,        // 상하좌우
		WALL_TOP_LEFT_CORNER = 8,
		// ... 추가 가능
	};

	struct ObjectDatas {
		Tile::State state = Tile::FLOOR;
		Tile* tile = nullptr;
	};

	GameMap();
	~GameMap();

	void Update();
	void Render();
	void Edit();


	void Generate();
	void SelectWallShape(int x, int y, Tile* object);
//	void SelectWallShape(Tile* object);

private:
	Vector2 tileCount = { 200,150 };
	Vector2 tileSize = { 16,16 };
	int size = tileCount.x * tileCount.y;
	int objectCount = 0;

	vector<vector<Tile::State>> mapData;
	vector<vector<ObjectDatas*>> objectDatas;

	vector<Tile*> tiles;
	Quad* quad;

	Quad* objectQuad;

	vector<InstanceData> instances;
	VertexBuffer* instanceBuffer;

	vector<InstanceData> objectInstances;
	VertexBuffer* objectInstanceBuffer;

	vector<Tile*> objects;

	std::unordered_map<int, int> wallShapeTable4Dir = {
	{0b0000, 0},  // none
	{0b0001, 1},  // ↑
	{0b0010, 2},  // ↓
	{0b0011, 3},  // ↑↓
	{0b0100, 4},  // ←
	{0b0101, 5},  // ↑←
	{0b0110, 6},  // ↓←
	{0b0111, 7},  // ↑↓←
	{0b1000, 8},  // →
	{0b1001, 9},  // ↑→
	{0b1010,10},  // ↓→
	{0b1011,11},  // ↑↓→
	{0b1100,12},  // ←→
	{0b1101,13},  // ↑←→
	{0b1110,14},  // ↓←→
	{0b1111,15},  // ↑↓←→ (all)
	};




};