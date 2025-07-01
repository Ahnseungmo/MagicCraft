#pragma once

class Tile : public RectCollider {

public:

	enum State {
		FLOOR,
		ROAD,
		WALL,
		WATER
	};

	Tile(Vector2 size,State state = State::FLOOR,int data = 0);
	~Tile();
	void SetInstance(InstanceData instance) { this->instance = instance; }

	void SetState(State state) { this->state = state; }
	State GetState() { return state; }

	void SetTilesetPos(Vector2 pos) { this->tilesetPos = pos; }
    void CalTilesetPos();
	Vector2 GetTilesetPos() { return tilesetPos; }

	void SetTileType(int index) { this->tileType = index; }

    void Render();

    void CalTileData(int data);

    void UpdateWorld();

    vector<Vector2> GetQuaterTilePos() { return quaterTilePos; }
    vector<Vector2> GetQuaterTileShape(){ return quaterTileShape; }
    Vector2 GetQuaterTilePos(int index) { return quaterTilePos.at(index); }
    Vector2 GetQuaterTileShape(int index) { return quaterTileShape.at(index); }

private:
	State state = FLOOR;
	Vector2 tilesetPos = { 0,0 };
	InstanceData instance;
	int tileType;

    vector<Vector2> quaterTilePos = { {0,0}, {0,0}, {0,0}, {0,0}};
    vector<Vector2> quaterTileShape = { {0,0}, {0,0}, {0,0}, {0,0} };
    vector<int> quaterTileShapeData = {0,0,0,0};

    unordered_map<int, Vector2> wallShapePos = {
        { 0b0101,{3,6} },
        { 0b0110,{3,4} },
        { 0b1001,{1,6} },
        { 0b1010,{1,4} },
        { 0b1110,{2,4} },
        { 0b1101,{2,6} },
        { 0b1011,{1,5} },
        { 0b0111,{3,5} },
        { 0b1111,{2,5} }
    };
    unordered_map<int, Vector2> floorShapePos = {
    { 0,{4,8} },
    { 0b0101,{4,8} },
    { 0b0110,{4,8} },
    { 0b1001,{4,8} },
    { 0b1010,{4,8} },
    { 0b1110,{4,8} },
    { 0b1101,{4,8} },
    { 0b1011,{4,8} },
    { 0b0111,{4,8} },
    { 0b1111,{4,8} }
    };
	vector<Vector2>wallTileShapePos = {
    {0, 4}, // 0
    {1, 4}, // 1
    {2, 4}, // 2
    {3, 4}, // 3
    {4, 4}, // 4
    {5, 4}, // 5
    {0, 5}, // 6
    {1, 5}, // 7
    {2, 5}, // 8
    {3, 5}, // 9
    {4, 5}, //10
    {5, 5}, //11
    {0, 6}, //12
    {1, 6}, //13
    {2, 6}, //14
    {3, 6}, //15
    {4, 6}, //16
    {5, 6}, //17
    {0, 7}, //18
    {1, 7}, //19
    {2, 7}, //20
    {3, 7}, //21
    {4, 7}, //22
    {5, 7}  //23
	};

    vector<Vector2>floorTileShapePos = {
        {0, 8}, // 0
        {1, 8}, // 1
        {2, 8}, // 2
        {3, 8}, // 3
        {4, 8}  // 4
    };
};