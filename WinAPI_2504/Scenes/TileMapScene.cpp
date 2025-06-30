#include "Framework.h"
#include "TileMapScene.h"

TileMapScene::TileMapScene()
{
	gameMap = new GameMap();
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
