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



	EnemyManager::Get()->SetGameMap(gameMap);
	EnemyManager::Get()->SetPlayer(player);
	EnemyManager::Get()->SetEnemys();

	EnemyManager::Get()->SetGameMap(gameMap);
	EnemyManager::Get()->SetAStar(aStar);

//	EnemyManager::Get()->Spawn(Vector2(32,32));
//	EnemyManager::Get()->Spawn(player->GetGlobalPosition());
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
	int pos[2];
	float globalPos[2];
	Vector2 gp = player->GetGlobalPosition();
	globalPos[0] = gp.x;
	globalPos[1] = gp.y;
	Vector2 p = gameMap->CalPosToTilePos(gp);
	pos[0] = p.x;
	pos[1] = p.y;
	ImGui::InputFloat2("global", globalPos);
	ImGui::InputInt2("pos", pos);

	vector<Vector2> biomes = gameMap->GetBiomeBassTilePos();
	float biome1[2] = { biomes[0].x,biomes[1].y };
	ImGui::InputFloat2("0", biome1);
	float biome2[2] = { biomes[1].x,biomes[1].y };
	ImGui::InputFloat2("1", biome2);
	float biome3[2] = { biomes[2].x,biomes[2].y };
	ImGui::InputFloat2("2", biome3);
	float biome4[2] = { biomes[3].x,biomes[3].y };
	ImGui::InputFloat2("3", biome4);
	float biome5[2] = { biomes[4].x,biomes[4].y };
	ImGui::InputFloat2("4", biome5);

	/*
	float biome1[2] = { biomes[0].x * 32,biomes[1].y * 32 };
	ImGui::InputFloat2("0", biome1);
	float biome2[2] = { biomes[1].x*32,biomes[1].y * 32 };
	ImGui::InputFloat2("1", biome2);
	float biome3[2] = { biomes[2].x * 32,biomes[2].y * 32 };
	ImGui::InputFloat2("2", biome3);
	float biome4[2] = { biomes[3].x * 32,biomes[3].y * 32 };
	ImGui::InputFloat2("3", biome4);
	float biome5[2] = { biomes[4].x * 32,biomes[4].y * 32 };
	ImGui::InputFloat2("4", biome5);
	
	*/

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
