#pragma once

class Tile : public RectCollider {

public:

    enum State {
        FLOOR,
        ROAD,
        WALL,
        WATER,
        PLAYER_SPAWN

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
        /*
{ 0b00010101,{3,6} },
{ 0b01000110,{3,4} },
{ 0b00101001,{1,6} },
{ 0b10001010,{1,4} },

{ 0b11001110,{2,4} },
{ 0b00111101,{2,6} },
{ 0b10101011,{1,5} },
{ 0b01010111,{3,5} },
*/
        { 0b00000101,{3,6} }, //����
        { 0b00000110,{3,4} }, //����
        { 0b00001001,{1,6} }, //���
        { 0b00001010,{1,4} }, //�Ͽ�

        { 0b00001110,{2,4} }, //���¿�
        { 0b00001101,{2,6} }, //���¿�
        { 0b00001011,{1,5} }, //���Ͽ�
        { 0b00000111,{3,5} }, //������

        { 0b01111111,{4,4} }, //�Ͽ� ����
        { 0b10111111,{5,4} }, //���� ����
        { 0b11011111,{4,5} }, //��� ����
        { 0b11101111,{5,5} }, //���� ����

        { 0b11111111,{2,5} }, //Ǯ
        { 0,{1,10} }          //���� �˻�
 //       { 0,{4,7} }
    };

    unordered_map<int, Vector2> waterShapePos = {
        { 0b00000101,{4,13} }, //����
        { 0b00000110,{4,9} }, //����
        { 0b00001001,{0,13} }, //���
        { 0b00001010,{0,9} }, //�Ͽ�

        { 0b00001110,{2,9} }, //���¿�
        { 0b00001101,{2,13} }, //���¿�
        { 0b00001011,{0,11} }, //���Ͽ�
        { 0b00000111,{4,11} }, //������

        { 0b01111111,{2,15} }, //�Ͽ� ����
        { 0b10111111,{1,15} }, //���� ����
        { 0b11011111,{2,14} }, //��� ����
        { 0b11101111,{1,14} }, //���� ����

        { 0b11111111,{2,11} }, //Ǯ
        { 0,{4,7} }          //���� �˻�
        //       { 0,{4,7} }
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