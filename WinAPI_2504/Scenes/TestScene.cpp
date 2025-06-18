#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	DataManager::Get()->LoadFrames("Resources/Textures/MagicCraft/Spell");

	spell = new Spell();
	SandBag = new RectCollider({ 100, 100 });
	SandBag->SetLocalPosition(CENTER_X + CENTER_X / 2, CENTER_Y);
	SandBag->UpdateWorld();

	player = new Player();
	player->SetLocalPosition(CENTER);
	player->UpdateWorld();
	
}

TestScene::~TestScene()
{
	delete spell;
	delete player;
}

void TestScene::Update()
{
	player->Update();
	Vector2 playerPos = player->GetGlobalPosition();
	if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
		spell->SetLocalScale(1.0f, 1.0f);
		spell->Spawn(playerPos, ((mousePos) - playerPos).GetNormalized(), {32,10});
	}
	if (Input::Get()->IsKeyDown(VK_RBUTTON)) {
		spell->SetLocalScale(2.0f, 2.0f);
		spell->Spawn(playerPos, ((mousePos) - playerPos).GetNormalized(), { 32,10 });
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
	player->Render();
}

void TestScene::GUIRender()
{
	player->Edit();
}
