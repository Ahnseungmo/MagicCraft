#include "Framework.h"

PlayerStateUI::PlayerStateUI()
{
	hpBar = new ValueBar(L"Resources/Textures/MagicCraft/UI/ValueRed_120x8.png");
//	hpBar->SetLocalScale(0, 2.0f);
	mpBar = new ValueBar(L"Resources/Textures/MagicCraft/UI/ValueBlue_120x8.png");

	hpBar->SetParent(this);
	mpBar->SetParent(this);
	
	hpBack = new Quad(L"Resources/Textures/MagicCraft/UI/ValueBar_128x16.png");
//	hpBack->SetLocalScale(0, 2.0f);
	mpBack = new Quad(L"Resources/Textures/MagicCraft/UI/ValueBar_128x16.png");

	mpBack->SetParent(this);
	hpBack->SetParent(this);

	mpBack->SetLocalPosition(0, -16);
	mpBar->SetLocalPosition(0, -16);

	hpBar->UpdateWorld();
	mpBar->UpdateWorld();
	hpBack->UpdateWorld();
	mpBack->UpdateWorld();
}

PlayerStateUI::~PlayerStateUI()
{
	delete hpBar;
	delete mpBar;
	delete hpBack;
	delete mpBack;

}


void PlayerStateUI::Update() {
	hpBar->SetValue(player->GetHp() / player->GetHpMax());
	mpBar->SetValue(player->GetMp() / player->GetMpMax());

	UpdateWorld();
	hpBar->UpdateWorld();
	mpBar->UpdateWorld();
	hpBack->UpdateWorld();
	mpBack->UpdateWorld();

}
void PlayerStateUI::Render() {
	hpBar->Render();
	mpBar->Render();
	hpBack->Render();
	mpBack->Render();
}