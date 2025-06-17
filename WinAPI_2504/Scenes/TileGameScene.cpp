#include "Framework.h"
#include "TileGameScene.h"

TileGameScene::TileGameScene()
{
	tileMap = new TileMap("Resources/TextData/Stage1.map");
	tileMap->SetLocalPosition(0, SCREEN_HEIGHT);	
	tileMap->SetTag("TileMap");
	tileMap->Load();
	tileMap->UpdateWorld();

	tank = new Tank();
	tank->SetTileMap(tileMap);

	aStar = new AStar(tileMap);
}

TileGameScene::~TileGameScene()
{
	delete tileMap;
	delete tank;
	delete aStar;
}

void TileGameScene::Update()
{
	//tileMap->UpdateWorld();
	if (Input::Get()->IsKeyDown(VK_LBUTTON))
	{
		int start = aStar->FindCloseNode(tank->GetLocalPosition());
		int end = aStar->FindCloseNode(mousePos);

		tank->SetPath(aStar->GetPath(start, end));
	}

	tank->Update();
}

void TileGameScene::Render()
{
	tileMap->Render();
	tank->Render();
	aStar->Render();
}

void TileGameScene::GUIRender()
{
	tileMap->Edit();
}
