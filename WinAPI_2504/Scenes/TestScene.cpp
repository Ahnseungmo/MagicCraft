#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	DataManager::Get()->LoadFrames("Resources/Textures/MagicCraft/Spell");

	spell = new Spell();
	SandBag = new RectCollider({ 100, 100 });
	SandBag->SetLocalPosition(CENTER_X + CENTER_X / 2, CENTER_Y);
	SandBag->UpdateWorld();

	
}

TestScene::~TestScene()
{
	delete spell;
}

void TestScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
		spell->Spawn(CENTER, (mousePos - CENTER).GetNormalized(), {32,10});
	}
	if (Input::Get()->IsKeyDown(VK_RBUTTON)) {
		spell->Spawn(CENTER, (mousePos - CENTER).GetNormalized(),{100,50});
	}
	spell->Update();
	if(spell->GetState() == Spell::State::Moving)
	if (spell->IsRectCollision(SandBag, nullptr)) {
		spell->Hit();
	}

}

void TestScene::Render()
{
	spell->Render();
	SandBag->Render();
}
