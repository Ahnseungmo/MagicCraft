#include "Framework.h"


Tile::Tile(Vector2 size, State state, int data) : RectCollider(size), state(state)
{
	tileType = 0;
	if(state != Tile::FLOOR) CalTileData(data);
	CalTilesetPos();
	quaterTilePos.reserve(4);



}

Tile::~Tile()
{
}

void Tile::CalTilesetPos()
{
	if (state == WALL) {
//		SetTilesetPos(wallTileShapePos.at(tileType));	
		for (int i = 0; i < 4; i++) {

			try {
				int data = quaterTileShapeData.at(i);
				auto it = wallShapePos.find(data);
				if (it == wallShapePos.end()) {
					data &= 0b1111;
				}
				quaterTileShape.at(i) = wallShapePos.at(data);

			}
			catch (const std::out_of_range& oor){
				quaterTileShape.at(i) = wallShapePos.at(0);
			}
		}
	}
	else if (state == WATER) {
		//		SetTilesetPos(wallTileShapePos.at(tileType));	
		for (int i = 0; i < 4; i++) {

			try {
				int data = quaterTileShapeData.at(i);
				auto it = waterShapePos.find(data);
				if (it == waterShapePos.end()) {
					data &= 0b1111;
				}
				quaterTileShape.at(i) = waterShapePos.at(data);

			}
			catch (const std::out_of_range& oor) {
				quaterTileShape.at(i) = waterShapePos.at(0);
			}
		}
	}


	else {
//		SetTilesetPos(floorTileShapePos.at(4));
		for (int i = 0;i < 4;i++)
			quaterTileShape.at(i) = floorShapePos.at(0);
	}
}

void Tile::Render()
{
	if (state == FLOOR) return;
	RectCollider::Render();
}

void Tile::CalTileData(int data) {
	int type = 0;
	int quaterData[4][4] = {0,};
	quaterData[1][1] = 1;
	quaterData[1][2] = 1;
	quaterData[2][1] = 1;
	quaterData[2][2] = 1;

	if (data & 0b00000001) {
		quaterData[1][0] = 1;
		quaterData[2][0] = 1;
	}
	if (data & 0b00000010) {
		quaterData[1][3] = 1;
		quaterData[2][3] = 1;
	}
	if (data & 0b00000100) {
		quaterData[0][1] = 1;
		quaterData[0][2] = 1;
	}
	if (data & 0b00001000) {
		quaterData[3][1] = 1;
		quaterData[3][2] = 1;
	}
	if (data & 0b00010000) {
		quaterData[0][0] = 1;
	}
	if (data & 0b00100000) {
		quaterData[3][0] = 1;
	}
	if (data & 0b01000000) {
		quaterData[0][3] = 1;
	}
	if (data & 0b10000000) {
		quaterData[3][3] = 1;
	}


	vector<Vector2> pos = {
		{1,1},
		{1,2},
		{2,1},
		{2,2}
	};
	vector<Vector2> checkPos = {
		{0,-1},
		{0,1},
		{-1,0},
		{1,0},

		{-1,-1},
		{1,-1},
		{-1,1},
		{1,1}
	};


	for (int i = 0;i < 4;i++) {
		int checkData = 0;
		int check = 0b00000001;
		for (int j = 0;j < checkPos.size();j++) {
			Vector2 target = pos.at(i) + checkPos.at(j);
			if (quaterData[(int)target.x][(int)target.y]) {
				checkData |= check;
			}
			check <<= 1;
		}
		quaterTileShapeData[i] = checkData;
	}
}

void Tile::UpdateWorld() {
	RectCollider::UpdateWorld();
	int i = 0;
	for (int x = 0; x < 2;x++) {
		for (int y = 0; y < 2; y++) {
			Vector2 halfSize = Size() * 0.5;
			Vector2 pos = GetLocalPosition() + Vector2(-halfSize.x*0.5, halfSize.y * 0.5);
			quaterTilePos[i++] = pos + Vector2{ x * halfSize.x , -y * halfSize.y };
		}
	}
}