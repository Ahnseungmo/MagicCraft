#include "framework.h"

GameMap::GameMap(Vector2 count) : tileCount(count)
{
	quad = new Quad(L"Resources/Textures/MagicCraft/TileMap/BiomeTiles.png", Vector2(),
		Vector2(1.0f / 30.0f, 1.0f / 16.0f));
	quad->GetMaterial()->SetShader(L"SpriteInstancing.hlsl");

	int size = count.x * count.y;
	tileDatas.reserve(size);
	floors.reserve(size);
	for (int i = 0;i < size;i++) {
		floors.push_back(new Tile(tileSize));
		float x = (i % ((int)count.x)) * tileSize.x;
		float y = (i / ((int)count.x)) * tileSize.y;
		y = (count.y*tileSize.y - tileSize.y/2) - y;
		x = tileSize.x / 2 + x;
		floors.back()->SetParent(this);
		floors.back()->SetLocalPosition({ x,y });
		floors.back()->SetZPos(0.9f);
		floors.back()->UpdateWorld();
		tileDatas.push_back(new TileData());
	}

	floorInstances.resize(floors.size()*4);
	SetInstanceBuffer(floors, floorInstances, floorInstanceBuffer);
	
	mapGenerator = new MapGenerator(count.x, count.y, 40);
	mapGenerator->generate();
	biomeBassTilePos = mapGenerator->GetBiomeBaseTilePos();
	MapGenerate();

	objectInstances.resize(objects.size()*4);
	SetInstanceBuffer(objects, objectInstances, objectInstanceBuffer);


}

GameMap::~GameMap()
{
	for (auto& floor : floors) {
		delete floor;
	}
	floors.clear();
}

void GameMap::Update()
{
	/*
	floorInstanceBuffer->Update(floorInstances.data(), 0);
	objectInstanceBuffer->Update(objectInstances.data(),0);
	*/
}

void GameMap::Render()
{
	floorInstanceBuffer->Set(1);

	quad->SetWorld();
	quad->GetMaterial()->Set();
	quad->GetMesh()->DrawInstanced(floorInstances.size());

	objectInstanceBuffer->Set(1);

	quad->SetWorld();
	quad->GetMaterial()->Set();
	quad->GetMesh()->DrawInstanced(objectInstances.size());
	
	/*
	for (auto& tile : objects) {
		tile->Render();
	}
	*/
}

void GameMap::Edit()
{
}

void GameMap::SetInstanceBuffer(vector<Tile*> tiles, vector<InstanceData>& instances ,VertexBuffer*& buffer)
{

	int i = 0;
	int j = 0;
	for (InstanceData& instance : instances)
	{
		if (j >= 4) {
			i++;
			j = 0;
		}
		float x = tiles.at(i)->GetQuaterTilePos(j).x;
		float y = tiles.at(i)->GetQuaterTilePos(j).y;
		float z = tiles.at(i)->GetZPos();
		Matrix world = XMMatrixTranslation(x, y, z);

		instance.world = XMMatrixTranspose(world);
		instance.maxFrame = Float2(30, 16);

		float frameX = tiles.at(i)->GetQuaterTileShape(j).x;
		float frameY = tiles.at(i)->GetQuaterTileShape(j).y;

		instance.curFrame = Float2(frameX, frameY);
		j++;
		
	}
	buffer = new VertexBuffer(instances.data(), sizeof(InstanceData), instances.size());

}

void GameMap::MapGenerate()
{
	/*
	tileDatas[0]->state = Tile::WALL;
	tileDatas[1]->state = Tile::WALL;
	tileDatas[2]->state = Tile::WALL;
	tileDatas[3]->state = Tile::WALL;
	*/
	/*
	for (int y = tileCount.y - 3; y < tileCount.y; y++) {
		for (int x = 0; x < 3;x++) {
			tileDatas[CalTilePos({(float)x,(float)y})]->state = Tile::WALL;

		}
	}
	*/
	
	int c = 0;
	for (int y = 0; y < tileCount.y; y++) {
		for (int x = 0; x < tileCount.x; x++) {
			Tile::State state;
			switch (mapGenerator->GetMapData().at(y).at(x)) {
				case 0:
					state = Tile::FLOOR;
					break;

				case 1:
					state = Tile::WALL;
					break;

				case 2://water
					state = Tile::WATER;
					break;

				case 3://playerSpawn
					state = Tile::PLAYER_SPAWN;
					break;
				default:
					state = Tile::FLOOR;
					break;

			}
			if (state != Tile::FLOOR) {
				tileDatas[c]->state = state;
			}
			c++;
		}
	}
	
	
	for (int i = 0;i < tileDatas.size();i++) {
		Tile::State state = tileDatas[i]->state;
		if (state == Tile::WALL || state == Tile::WATER) {

			tileDatas[i]->object = new Tile(tileSize,state, NeighTileData(i));
			tileDatas[i]->object->SetParent(this);
			tileDatas[i]->object->SetLocalPosition(floors[i]->GetLocalPosition());
			tileDatas[i]->object->SetZPos(0.8f);
			tileDatas[i]->object->UpdateWorld();
			objects.push_back(tileDatas[i]->object);
		}
		else if (state == Tile::PLAYER_SPAWN) {
			playerSpawnPoint = floors[i]->GetGlobalPosition();
		}
	}
}

int GameMap::NeighTileData(int index)
{
	int data = 0;
	int checkData = 0b00000001;

	Vector2 pos = CalTilePos(index);
	Tile::State state = tileDatas.at(index)->state;
	/*
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) continue;

			Vector2 target = { pos.x + x,pos.y + y };
			bool check = target.x < 0 || target.x >= tileCount.x || target.y < 0 || target.y >= tileCount.y;
			if (check || tileDatas.at(CalTilePos(target))->state == state)
				data |= checkData;

			checkData <<= 1;
		}
	}
	*/
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

	for (int i = 0;i < checkPos.size();i++) {
		Vector2 target = pos + checkPos.at(i);
		bool check = target.x < 0 || target.x >= tileCount.x || target.y < 0 || target.y >= tileCount.y;
		if (check || tileDatas.at(CalTilePos(target))->state == state)
			data |= checkData;
		checkData <<= 1;

	}
	return data;
}

Vector2 GameMap::CalTilePos(int index) {
	float x = index % (int)tileCount.x;
	float y = index / (int)tileCount.x;
	return { x,y };
}

int GameMap::CalTilePos(Vector2 pos)
{
	float x = pos.x;
	float y = pos.y * tileCount.x;
	return x+y;
}

void GameMap::MakeNodes(vector<Node*>& nodes)
{
	for (int i = 0;i < floors.size();i++) {
		Vector2 tilePos = floors.at(i)->GetGlobalPosition();
		Node* node = new Node(tilePos, nodes.size());
		Tile::State state = tileDatas.at(i)->state;
		if (state == Tile::WALL || state == Tile::WATER) {
			node->SetState(Node::Obstacle);
		}
		nodes.push_back(node);
	
	}
}


