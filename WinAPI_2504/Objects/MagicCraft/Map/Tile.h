#pragma once

class Tile : public RectCollider {

public:

	enum State {
		FLOOR,
		ROAD,
		WALL,
		WATER
	};

	Tile(Vector2 size);
	~Tile();
	void SetInstance(InstanceData instance) { this->instance = instance; }

	void SetState(State state) { this->state = state; }
	State GetState() { return state; }

	void SetTilesetPos(Vector2 pos) { this->tilesetPos = pos; }
    void CalTilesetPos();
	Vector2 GetTilesetPos() { return tilesetPos; }

	void SetTileType(int index) { this->tileType = index; }

private:
	State state = FLOOR;
	Vector2 tilesetPos = { 0,0 };
	InstanceData instance;
	int tileType;




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