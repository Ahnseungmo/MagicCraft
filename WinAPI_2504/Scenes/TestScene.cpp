#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	SpellManager::Get();
	DataManager::Get()->LoadFrames("Resources/Textures/MagicCraft/Spell");


	SandBag = new RectCollider({ 100, 100 });
	SandBag->SetLocalPosition(CENTER_X + CENTER_X / 2, CENTER_Y);
	SandBag->UpdateWorld();

	player = new Player();
	player->SetLocalPosition(CENTER);
	player->SetZPos(0.5);
	player->UpdateWorld();
	
	Environment::Get()->GetMainCamera()->SetTarget(player);
	Environment::Get()->GetMainCamera()->SetParent(player->GetCameraTransform());

	SpellOptionData* data = new SpellOptionData();
//	SpellManager::Get()->SetOptionShape(data, Arrow);
	SpellManager::Get()->SetOptionShape(data, Blade);
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

//	EnemyManager::Get()->Spawn({ 100,CENTER_Y });

	/*
	book = new SpellCustomUI();
	book->SetLocalPosition(CENTER);
	book->UpdateWorld();
	*/
}

TestScene::~TestScene()
{

	delete player;
	delete book;
	UIManager::Get()->Delete();
}

void TestScene::Update()
{
	if (!UIManager::Get()->IsPause()) {
		player->Update();
		Vector2 playerPos = player->GetGlobalPosition();
		Vector2 targetPos = mousePos + player->GetCameraTransform()->GetGlobalPosition();
		if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
			SpellManager::Get()->Spawn(playerPos, ((targetPos)-playerPos).GetNormalized(), SpellManager::Get()->GetSpellOptionData(0));
		}
		if (Input::Get()->IsKeyDown(VK_RBUTTON)) {
			SpellManager::Get()->Spawn(playerPos, ((targetPos)-playerPos).GetNormalized(), SpellManager::Get()->GetSpellOptionData(1));
		}

		SpellManager::Get()->Update();
//		EnemyManager::Get()->Update();
		SpellManager::Get()->HitCheck();

	}

	
	UIManager::Get()->Update();
}

void TestScene::Render()
{


	SandBag->Render();
	player->Render();
//	EnemyManager::Get()->Render();
	SpellManager::Get()->Render();
}

void TestScene::GUIRender()
{
	player->Edit();
	EnemyManager::Get()->Edit();
	
//	book->Render();
//	SpellCustomUI
	UIManager::Get()->Render();
	Vector2 playerPos = player->GetGlobalPosition();
	Vector2 targetPos = mousePos + player->GetCameraTransform()->GetGlobalPosition();

	ImGui::DragFloat("mouse x", &targetPos.x);
	ImGui::DragFloat("mouse y", &targetPos.y);

}
