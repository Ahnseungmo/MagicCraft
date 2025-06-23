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


	/*



	slot = new OptionButton();
	slot->SetParent(this);
	slot->SetLocalPosition({ (pageRight->GetSize() * 0.5).x ,0 });

	slot2 = new OptionButton();
	slot2->SetParent(this);
	slot2->SetLocalPosition({ (pageRight->GetSize() * 0.5).x  + 100,0 });


	slot->SetOption(optionPieace);


	slot2->SetOption(new Option(optionPieace));

	*/
	spellSlotsTransform = new Transform;
	spellSlotsTransform->SetParent(this);
	spellSlotsTransform->SetLocalPosition({ (pageRight->GetSize() * 0.5).x ,0 });
	spellSlotsTransform->UpdateWorld();

	int spellSlotSize = OPTION_SLOT_ROW * OPTION_SLOT_COL;
	slots.reserve(spellSlotSize);
	//int xposShift = (slot->Size().x + OPTION_SLOT_PADDING) * (OPTION_SLOT_ROW - 1) / 2;
	for (int i = 0; i < spellSlotSize; i++) {
		OptionButton* slot = new OptionButton();
		slot->SetParent(spellSlotsTransform);
		int xposShift = (slot->Size().x + OPTION_SLOT_PADDING) * (OPTION_SLOT_ROW - 1) / 2;
		slot->SetLocalPosition({ (slot->Size().x + OPTION_SLOT_PADDING) * (i%OPTION_SLOT_ROW) - xposShift, (slot->Size().y + OPTION_SLOT_PADDING) * -(i / OPTION_SLOT_ROW) });
		slot->UpdateWorld();
		slots.push_back(slot);
	}
	
	slots.back()->SetOption(new Option(optionPieace));

	slots.at(0)->SetOption(new Option(optionPieace));
	slots.at(0)->SetInfinity(true);

}

SpellCustomUI::~SpellCustomUI()
{
	delete backGround;

	delete pageLeft;
	delete pageRight;

	for (auto& slot : slots)
		delete slot;
	slots.clear();
}

void SpellCustomUI::Update()
{
	if (!isActive)return;
	backGround->UpdateWorld();
	pageLeft->UpdateWorld();
	pageRight->UpdateWorld();
	spellSlotsTransform->UpdateWorld();
	for (auto& slot : slots)
		slot->Update();


}

void SpellCustomUI::Render()
{
	if (!isActive)return;
	backGround->Render();
	pageLeft->Render();
	pageRight->Render();

	for (auto& slot : slots)
		slot->Render();


}
