#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	spell = new Spell();
}

TestScene::~TestScene()
{
	delete spell;
}

void TestScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
		spell->Spawn(CENTER, (mousePos - CENTER).GetNormalized(), {50,50});
	}
	if (Input::Get()->IsKeyDown(VK_RBUTTON)) {
		spell->Spawn(CENTER, (mousePos - CENTER).GetNormalized(),{100,50});
	}

	spell->Update();
}

void TestScene::Render()
{
	spell->Render();
}
