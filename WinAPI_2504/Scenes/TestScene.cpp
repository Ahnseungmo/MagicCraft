#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	SpellManager::Get();
	DataManager::Get()->LoadFrames("Resources/Textures/MagicCraft/Spell");

	spell = new Spell();
	SandBag = new RectCollider({ 100, 100 });
	SandBag->SetLocalPosition(CENTER_X + CENTER_X / 2, CENTER_Y);
	SandBag->UpdateWorld();

	player = new Player();
	player->SetLocalPosition(CENTER);
	player->UpdateWorld();
	
	SpellOptionData* data = new SpellOptionData();
	SpellManager::Get()->SetOptionShape(data, Arrow);
	SpellManager::Get()->SetOptionElement(data, Fire);
	SpellManager::Get()->SetOptionHoming(data);
	SpellManager::Get()->SetOptionHoming(data);


	delete SpellManager::Get()->GetSpellOptionData(0);
	SpellManager::Get()->SetSpellOptionData(0,data);


	data = new SpellOptionData();
	SpellManager::Get()->SetOptionShape(data, Arrow);
	SpellManager::Get()->SetOptionElement(data, Water);
	SpellManager::Get()->SetOptionUpScale(data);
	SpellManager::Get()->SetOptionUpScale(data);
	SpellManager::Get()->SetOptionUpScale(data);
	SpellManager::Get()->SetOptionPierce(data);
	SpellManager::Get()->SetOptionPierce(data);
	SpellManager::Get()->SetOptionPierce(data);
	SpellManager::Get()->SetOptionPierce(data);
	SpellManager::Get()->SetOptionPierce(data);
	SpellManager::Get()->SetOptionPierce(data);
	SpellManager::Get()->SetOptionPierce(data);

	delete SpellManager::Get()->GetSpellOptionData(1);
	SpellManager::Get()->SetSpellOptionData(1, data);

	EnemyManager::Get()->Spawn({ 100,CENTER_Y });

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
//		spell->SetLocalScale(1.0f, 1.0f);
		spell->Spawn(playerPos, ((mousePos) - playerPos).GetNormalized(), {32,10},SpellManager::Get()->GetSpellOptionData(0));
	}
	if (Input::Get()->IsKeyDown(VK_RBUTTON)) {
//		spell->SetLocalScale(2.0f, 2.0f);
		spell->Spawn(playerPos, ((mousePos) - playerPos).GetNormalized(), { 32,10 }, SpellManager::Get()->GetSpellOptionData(1));
	}
	spell->Update();
	if(spell->GetState() == Spell::State::Moving)
	if (spell->IsRectCollision(SandBag, nullptr)) {
		spell->Hit();
	}
	EnemyManager::Get()->Update();
	EnemyManager::Get()->HitCheck(spell);

}

void TestScene::Render()
{
	spell->Render();
	SandBag->Render();
	player->Render();
	EnemyManager::Get()->Render();
}

void TestScene::GUIRender()
{
	player->Edit();
	EnemyManager::Get()->Edit();
}
