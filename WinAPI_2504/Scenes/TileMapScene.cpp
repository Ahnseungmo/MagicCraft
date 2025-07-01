#include "Framework.h"
#include "TileMapScene.h"

TileMapScene::TileMapScene()
{
	gameMap = new GameMap({ 200,150 });
	Environment::Get()->GetMainCamera()->SetLocalPosition(gameMap->GetPlayerSpawnPoint() - Vector2(SCREEN_WIDTH,SCREEN_HEIGHT)*0.5);
//	gameMap = new GameMap({ 4,4 });
}

TileMapScene::~TileMapScene()
{
	delete gameMap;
}

void TileMapScene::Update()
{
}

void TileMapScene::Render()
{
	gameMap->Render();
}

void TileMapScene::GUIRender()
{

}
