#include "Framework.h"

SpellCustomUI::SpellCustomUI() : RectCollider({500,500})
{
	isActive = false;
	backGround = new Quad(L"Resources/Textures/MagicCraft/UI/Book/BookCover.png");
	backGround->SetParent(this);
	pageLeft = new Quad(L"Resources/Textures/MagicCraft/UI/Book/BookPageLeft.png");
	pageLeft->SetParent(this);
	pageLeft->SetLocalPosition({ -(pageLeft->GetSize() * 0.5).x ,0});
	pageRight = new Quad(L"Resources/Textures/MagicCraft/UI/Book/BookPageRight.png");
	pageRight->SetParent(this);
	pageRight->SetLocalPosition({ (pageRight->GetSize() * 0.5).x ,0 });


	optionPieace = new Option();

	optionPieace->SetEvent(std::bind(
			[](SpellManager* manager, void* data) {
			manager->SetOptionPierce(static_cast<SpellOptionData*>(data));
		},
		SpellManager::Get(), std::placeholders::_1));

	optionPieace->SetImage(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Piearce.png"));






	slot = new OptionButton();
	slot->SetParent(this);
	slot->SetLocalPosition({ (pageRight->GetSize() * 0.5).x ,0 });

	slot2 = new OptionButton();
	slot2->SetParent(this);
	slot2->SetLocalPosition({ (pageRight->GetSize() * 0.5).x  + 100,0 });


	slot->SetOption(optionPieace);


	slot2->SetOption(new Option(optionPieace));



}

SpellCustomUI::~SpellCustomUI()
{
	delete backGround;

	delete pageLeft;
	delete pageRight;
	delete slot;
	delete slot2;
}

void SpellCustomUI::Update()
{
	if (!isActive)return;
	backGround->UpdateWorld();
	pageLeft->UpdateWorld();
	pageRight->UpdateWorld();
	slot->Update();
	slot2->Update();

}

void SpellCustomUI::Render()
{
	if (!isActive)return;
	backGround->Render();
	pageLeft->Render();
	pageRight->Render();
	slot->Render();
	slot2->Render();


}
