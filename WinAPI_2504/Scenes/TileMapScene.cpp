#include "Framework.h"
#include "TileMapScene.h"

TileMapScene::TileMapScene()
{

//	gameMap = new GameMap({ 200,150 });
//	gameMap = new GameMap({ 100,100 });
	gameMap = new GameMap({ 200,200 });
	//	Environment::Get()->GetMainCamera()->SetLocalPosition(gameMap->GetPlayerSpawnPoint() - Vector2(SCREEN_WIDTH,SCREEN_HEIGHT)*0.5);
	aStar = new MapAStar(gameMap);

	SetGameMapBiome();

	gameMap->SetInstanceBuffers();

	player = new Player();
	player->SetLocalPosition(gameMap->GetPlayerSpawnPoint());
	player->SetZPos(0.2f);
	player->UpdateWorld();

	Environment::Get()->GetMainCamera()->SetTarget(player);
	Environment::Get()->GetMainCamera()->SetParent(player->GetCameraTransform());

	EnemyManager::Get()->SetAStar(aStar);
	EnemyManager::Get()->SetPlayer(player);
	EnemyManager::Get()->SetGameMap(gameMap);
//	EnemyManager::Get()->Spawn(Vector2(32,32));
	EnemyManager::Get()->Spawn(player->GetGlobalPosition());
//	Collider::SwitchDraw();

	player->SetMap(gameMap);



}

TileMapScene::~TileMapScene()
{
	delete gameMap;
	delete aStar;
	delete player;
	EnemyManager::Get()->Delete();
}

void TileMapScene::Update()
{
	gameMap->Update();
	player->Update();
	EnemyManager::Get()->Update();
}

void TileMapScene::Render()
{
	gameMap->Render();
//	aStar->Render();
	player->Render();
	EnemyManager::Get()->Render();
}

void TileMapScene::GUIRender()
{
	/*
	int pos[2];
	Vector2 p = player->GetGlobalPosition();
	p = gameMap->CalPosToTilePos(p);
	pos[0] = p.x;
	pos[1] = p.y;
	ImGui::InputInt2("pos", pos);

	int pathSize[5];
	int pr[4];
	for (int i = 0;i < 5;i++) {

		int start = gameMap->CalPosToIndex(player->GetGlobalPosition());
		int end = gameMap->CalTilePosToIndex(gameMap->GetBiomeBassTilePos().at(i));

		pathSize[i] = aStar->GetPath(start,end).size();
		if (i > 0) pr[i - 1] = pathSize[i];
	}
	ImGui::InputInt("home", &pathSize[0]);
	ImGui::InputInt4("Biomes", pr);

	EnemyManager::Get()->Edit();
	*/
}

void TileMapScene::SetGameMapBiome()
{
	vector<Vector2> biome = gameMap->GetBiomeBassTilePos();
	vector<Tile*> floors = gameMap->GetFloors();

	int index = 0;
	for (auto& floor : floors) {
		/*
		int start = index;
		vector<int> pathSize;
		for (int i = 0; i < biome.size();i++) {
			int end = gameMap->CalTilePosToIndex(gameMap->GetBiomeBassTilePos().at(i));
			pathSize.push_back(aStar->GetPathToTarget(start, end, 1).size());
		}
		int min = pathSize.at(0);
		int minIndex = 0;
		for (int i = 0;i < pathSize.size();i++) {
			if (pathSize.at(i) < min) {
				min = pathSize.at(i);
				minIndex = i;
			}
		}
		*/

		float minDistance = Vector2::Distance(floor->GetGlobalPosition(), biome.at(0) * 32);
		int minIndex = 0;
		for (int i = 1;i < biome.size();i++) {
			float distance = Vector2::Distance(floor->GetGlobalPosition(), biome.at(i) * 32);
			if (distance < minDistance) {
				minDistance = distance;
				minIndex = i;
			}
		}
		GameMap::TileData* data = gameMap->GetTileData(index);

		data->biome = minIndex;

		index++;
	}
}
