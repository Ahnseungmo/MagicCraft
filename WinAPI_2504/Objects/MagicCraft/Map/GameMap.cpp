#include "framework.h"

GameMap::GameMap()
{

	quad = new Quad(L"Resources/Textures/MagicCraft/TileMap/BiomeTiles.png", Vector2(),
		Vector2(1.0f / 30.0f, 1.0f / 16.0f));
	quad->GetMaterial()->SetShader(L"SpriteInstancing.hlsl");


	objectQuad = new Quad(L"Resources/Textures/MagicCraft/TileMap/BiomeTiles.png", Vector2(),
		Vector2(1.0f / 30.0f, 1.0f / 16.0f));
	objectQuad->GetMaterial()->SetShader(L"SpriteInstancing.hlsl");

//	quad->GetMaterial()->SetShader(L"Instancing.hlsl");



	tiles.reserve(tileCount.x * tileCount.y);


	float mapLeft = tileSize.x/2 ;
	float mapBottom = tileSize.y/2 ;

	for (int y = 0; y < tileCount.y; y++) {
		vector<Tile::State> mapLineData;
		vector<ObjectDatas*> objectLineData;
		for (int x = 0; x < tileCount.x; x++) {
			tiles.push_back(new Tile(tileSize));
			tiles.back()->SetParent(this);
			tiles.back()->SetLocalPosition(mapLeft + tileSize.x * x, mapBottom + tileSize.y * y);
			tiles.back()->SetZPos(0.9);
			tiles.back()->UpdateWorld();
			tiles.back()->SetState(Tile::FLOOR);
			tiles.back()->CalTilesetPos();
			mapLineData.push_back(Tile::FLOOR);
			objectLineData.push_back(new ObjectDatas());
		}
		mapData.push_back(mapLineData);
		objectDatas.push_back(objectLineData);
	}
	
	Generate();
	int i = 0;
	for (int y = 0; y < tileCount.y; y++) {
		for (int x = 0; x < tileCount.x; x++) {
			if (objectDatas[y][x]->state == Tile::WALL) {
				objectDatas[y][x]->tile = new Tile(tileSize);
				objectDatas[y][x]->tile->SetParent(this);
				objectDatas[y][x]->tile->SetLocalPosition(mapLeft + tileSize.x * x, mapBottom + tileSize.y * y);
				objectDatas[y][x]->tile->SetZPos(0.5);
				objectDatas[y][x]->tile->UpdateWorld();
				objectDatas[y][x]->tile->SetState(Tile::WALL);


				SelectWallShape(x, y, objectDatas[y][x]->tile);

				objects.push_back(objectDatas[y][x]->tile);
				objectCount++;
			}
		}
	}
	i = 0;
	for (int y = 0; y < tileCount.y; y++) {
		for (int x = 0; x < tileCount.x; x++) {
			if (objectDatas[y][x]->state == Tile::WALL) {
				SelectWallShape(x, y, objectDatas[y][x]->tile);
				objectDatas[y][x]->tile->CalTilesetPos();

			}
		}
	}


	i = 0;
	instances.resize(size);
	for (InstanceData& instance : instances)
	{

		float x = tiles.at(i)->GetGlobalPosition().x;
		float y = tiles.at(i)->GetGlobalPosition().y;
		float z = tiles.at(i)->GetZPos();
		Matrix world = XMMatrixTranslation(x, y, z);


		instance.world = XMMatrixTranspose(world);
		instance.maxFrame = Float2(30, 16);
		
		float frameX = tiles.at(i)->GetTilesetPos().x;
		float frameY = tiles.at(i)->GetTilesetPos().y;

		instance.curFrame = Float2(frameX,frameY);
		i++;
	}
	instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), size);

	
	i = 0;
	objectInstances.resize(objectCount);
	for (InstanceData& instance : objectInstances)
	{

		float x = objects.at(i)->GetGlobalPosition().x;
		float y = objects.at(i)->GetGlobalPosition().y;
		float z = objects.at(i)->GetZPos();
		Matrix world = XMMatrixTranslation(x, y, z);


		instance.world = XMMatrixTranspose(world);
		instance.maxFrame = Float2(30, 16);

		float frameX = objects.at(i)->GetTilesetPos().x;
		float frameY = objects.at(i)->GetTilesetPos().y;

		instance.curFrame = Float2(frameX, frameY);
		i++;
	}
	objectInstanceBuffer = new VertexBuffer(objectInstances.data(), sizeof(InstanceData), objectCount);



}

GameMap::~GameMap()
{
	delete quad;
	delete objectQuad;
	delete instanceBuffer;
}

void GameMap::Update()
{
}

void GameMap::Render()
{

	instanceBuffer->Set(1);

	quad->SetWorld();
	quad->GetMaterial()->Set();
	quad->GetMesh()->DrawInstanced(size);


	objectInstanceBuffer->Set(1);

	objectQuad->SetWorld();
	objectQuad->GetMaterial()->Set();
	objectQuad->GetMesh()->DrawInstanced(size);


}



void GameMap::Generate()
{

	objectDatas[0][0]->state = Tile::WALL;
	objectDatas[0][1]->state = Tile::WALL;
	objectDatas[1][0]->state = Tile::WALL;
	objectDatas[1][1]->state = Tile::WALL;

}

void GameMap::SelectWallShape(int x, int y, Tile* object)
{
	int data = 0;
	// 8방향 비트 설정
	// ↖
	if ((x - 1 >= 0 && y - 1 >= 0) && objectDatas[y - 1][x - 1]->state == Tile::WALL)
		data |= 0b00000001;
	// ↑
	if (y - 1 >= 0 && objectDatas[y - 1][x]->state == Tile::WALL)
		data |= 0b00000010;
	// ↗
	if ((x + 1 < tileCount.x && y - 1 >= 0) && objectDatas[y - 1][x + 1]->state == Tile::WALL)
		data |= 0b00000100;
	// ←
	if (x - 1 >= 0 && objectDatas[y][x - 1]->state == Tile::WALL)
		data |= 0b00001000;
	// →
	if (x + 1 < tileCount.x && objectDatas[y][x + 1]->state == Tile::WALL)
		data |= 0b00010000;
	// ↙
	if ((x - 1 >= 0 && y + 1 < tileCount.y) && objectDatas[y + 1][x - 1]->state == Tile::WALL)
		data |= 0b00100000;
	// ↓
	if (y + 1 < tileCount.y && objectDatas[y + 1][x]->state == Tile::WALL)
		data |= 0b01000000;
	// ↘
	if ((x + 1 < tileCount.x && y + 1 < tileCount.y) && objectDatas[y + 1][x + 1]->state == Tile::WALL)
		data |= 0b10000000;
	int base = ((data & 0b00000010) ? 1 : 0)      // ↑
		| ((data & 0b01000000) ? 2 : 0)      // ↓
		| ((data & 0b00001000) ? 4 : 0)      // ←
		| ((data & 0b00010000) ? 8 : 0);     // →

	int tileIndex = base;

	// 대각선 조건에 따른 확장
	if (!(data & 0b00000001)) tileIndex = 16; // ↖ 없음
	if (!(data & 0b00000100)) tileIndex = 17; // ↗ 없음
	if (!(data & 0b00100000)) tileIndex = 18; // ↙ 없음
	if (!(data & 0b10000000)) tileIndex = 19; // ↘ 없음

	if (!(data & 0b00000001) && !(data & 0b10000000)) tileIndex = 20; // ↖ + ↘ 없음
	if (!(data & 0b00000100) && !(data & 0b00100000)) tileIndex = 21; // ↗ + ↙ 없음

	object->SetTileType(tileIndex);

}

