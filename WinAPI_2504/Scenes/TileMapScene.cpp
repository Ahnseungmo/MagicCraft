#include "Framework.h"
#include "TileMapScene.h"

TileMapScene::TileMapScene()
{
	gameMap = new GameMap({ 200,150 });
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
