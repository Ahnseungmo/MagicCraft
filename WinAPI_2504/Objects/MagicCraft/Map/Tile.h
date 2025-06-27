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
	Vector2 GetTilesetPos() { return tilesetPos; }
private:
	State state = FLOOR;
	Vector2 tilesetPos = { 0,0 };
	InstanceData instance;
};