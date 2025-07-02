#include "Framework.h"
#include "TileMapScene.h"

TileMapScene::TileMapScene()
{

//	gameMap = new GameMap({ 200,150 });
	gameMap = new GameMap({ 100,100 });
//	Environment::Get()->GetMainCamera()->SetLocalPosition(gameMap->GetPlayerSpawnPoint() - Vector2(SCREEN_WIDTH,SCREEN_HEIGHT)*0.5);
	aStar = new MapAStar(gameMap);

	player = new Player();
	player->SetLocalPosition(gameMap->GetPlayerSpawnPoint());
	player->SetZPos(0.2f);
	player->UpdateWorld();

	Environment::Get()->GetMainCamera()->SetTarget(player);
	Environment::Get()->GetMainCamera()->SetParent(player->GetCameraTransform());

	EnemyManager::Get()->SetAStar(aStar);
	EnemyManager::Get()->SetPlayer(player);
	EnemyManager::Get()->SetGameMap(gameMap);
	EnemyManager::Get()->Spawn(player->GetGlobalPosition());
//	Collider::SwitchDraw();

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
	EnemyManager::Get()->Edit();
}
