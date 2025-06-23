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

	InitOption();
	InitSpellSlot();
	InitSpellSampleSlot();
	InitSpellMarker();

	sampleSlots.at(0)->SetOption(new Option(optionPiercing));
	sampleSlots.at(0)->SetInfinity(true);

	sampleSlots.at(1)->SetOption(new Option(optionHoming));
	sampleSlots.at(1)->SetInfinity(true);

	sampleSlots.at(2)->SetOption(new Option(optionDuplication));
	sampleSlots.at(2)->SetInfinity(true);

	sampleSlots.at(3)->SetOption(new Option(optionUpScale));
	sampleSlots.at(3)->SetInfinity(true);

	sampleSlots.at(4)->SetOption(new Option(optionReflect));
	sampleSlots.at(4)->SetInfinity(true);

	elementUI = new CircleUI(50);
	elementUI->SetParent(this);
	elementUI->SetLocalPosition({120,150});

	elementUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Fire.png"), Fire);
	elementUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Water.png"), Water);
	elementUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Ice.png"), Ice);
	elementUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Earth.png"), Earth);
	elementUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Tunder.png"), Tunder);
	elementUI->ImageRePosition();

	shapeUI = new CircleUI(50);
	shapeUI->SetParent(this);
	shapeUI->SetLocalPosition({ 300,150 });
	shapeUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Arrow.png"), Arrow);
	shapeUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Knife.png"), Knife);
	shapeUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Floor.png"), Floor);
	shapeUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Lay.png"), Lay);
	shapeUI->InsertIndex(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Ball.png"), Ball);
	shapeUI->ImageRePosition();
}

void SpellCustomUI::InitSpellMarker()
{
	spellMarkersTransform = new Transform();
	spellMarkersTransform->SetParent(this);
	spellMarkersTransform->SetLocalPosition({ (pageRight->GetSize()).x - 0,250 });
	spellMarkersTransform->UpdateWorld();

	spellMarkers.reserve(SPELL_MARKERS_SIZE);
	hoverTimers.resize(SPELL_MARKERS_SIZE);
	for (int i = 0;i < SPELL_MARKERS_SIZE;i++) {
		Button* marker = new Button(L"Resources/Textures/MagicCraft/UI/Book/Marker.png");
		marker->SetParent(spellMarkersTransform);
		marker->SetLocalPosition({ 0,-(i * 50.0f) });
		marker->UpdateWorld();
		spellMarkers.push_back(marker);
		hoverTimers.at(i) = 0.0f;
	}

}

void SpellCustomUI::InitSpellSlot()
{
	spellSlotsTransform = new Transform;
	spellSlotsTransform->SetParent(this);
	spellSlotsTransform->SetLocalPosition({ (pageRight->GetSize() * 0.5).x ,0 });
	spellSlotsTransform->UpdateWorld();

	int spellSlotSize = OPTION_SLOT_ROW * OPTION_SLOT_COL;
	slots.reserve(spellSlotSize);
	for (int i = 0; i < spellSlotSize; i++) {
		OptionButton* slot = new OptionButton();
		slot->SetParent(spellSlotsTransform);
		int xposShift = (slot->Size().x + OPTION_SLOT_PADDING) * (OPTION_SLOT_ROW - 1) / 2;
		slot->SetLocalPosition({ (slot->Size().x + OPTION_SLOT_PADDING) * (i % OPTION_SLOT_ROW) - xposShift, (slot->Size().y + OPTION_SLOT_PADDING) * -(i / OPTION_SLOT_ROW) });
		slot->UpdateWorld();
		slots.push_back(slot);
	}
}

void SpellCustomUI::InitSpellSampleSlot()
{

	spellSampleSlotsTransform = new Transform;
	spellSampleSlotsTransform->SetParent(this);
	spellSampleSlotsTransform->SetLocalPosition({ -(pageRight->GetSize() * 0.5).x ,200 });
	spellSampleSlotsTransform->UpdateWorld();

	sampleSlots.reserve(SAMPLE_SLOT_SIZE);
	for (int i = 0; i < SAMPLE_SLOT_SIZE; i++) {
		OptionButton* slot = new OptionButton();
		slot->SetParent(spellSampleSlotsTransform);
		int xposShift = (slot->Size().x + OPTION_SLOT_PADDING) * (OPTION_SLOT_ROW - 1) / 2;
		slot->SetLocalPosition({ -100, (slot->Size().y + OPTION_SLOT_PADDING) * -i });
		slot->UpdateWorld();
		sampleSlots.push_back(slot);
	}
}
void SpellCustomUI::InitOption()
{
	optionPiercing = new Option();

	optionPiercing->SetEvent(std::bind(
		[](SpellManager* manager, void* data) {
			manager->SetOptionPierce(static_cast<SpellOptionData*>(data));
		},
		SpellManager::Get(), std::placeholders::_1));

	optionPiercing->SetImage(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Piearce.png"));

	optionDuplication = new Option();
	optionDuplication->SetEvent(std::bind(
		[](SpellManager* manager, void* data) {
			manager->SetOptionDuplication(static_cast<SpellOptionData*>(data));
		},
		SpellManager::Get(), std::placeholders::_1));
	optionDuplication->SetImage(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Duplication.png"));

	optionHoming = new Option();
	optionHoming->SetEvent(std::bind(
		[](SpellManager* manager, void* data) {
			manager->SetOptionHoming(static_cast<SpellOptionData*>(data));
		},
		SpellManager::Get(), std::placeholders::_1));
	optionHoming->SetImage(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Homing.png"));

	optionUpScale = new Option();
	optionUpScale->SetEvent(std::bind(
		[](SpellManager* manager, void* data) {
			manager->SetOptionUpScale(static_cast<SpellOptionData*>(data));
		},
		SpellManager::Get(), std::placeholders::_1));
	optionUpScale->SetImage(new Quad(L"Resources/Textures/MagicCraft/UI/Book/UpScale.png"));

	optionReflect = new Option();
	optionReflect->SetEvent(std::bind(
		[](SpellManager* manager, void* data) {
			manager->SetOptionReflect(static_cast<SpellOptionData*>(data));
		},
		SpellManager::Get(), std::placeholders::_1));
	optionReflect->SetImage(new Quad(L"Resources/Textures/MagicCraft/UI/Book/Reflect.png"));
}
SpellCustomUI::~SpellCustomUI()
{
	delete backGround;

	delete pageLeft;
	delete pageRight;

	for (auto& slot : slots)
		delete slot;
	slots.clear();
	for (auto& slot : sampleSlots)
		delete slot;
	sampleSlots.clear();

	for (auto& marker : spellMarkers) {
		delete marker;
	}
	spellMarkers.clear();
	delete elementUI;
	delete shapeUI;
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

	spellSampleSlotsTransform->UpdateWorld();
	for (auto& slot : sampleSlots)
		slot->Update();

	spellMarkersTransform->UpdateWorld();

	for (int i = 0;i < SPELL_MARKERS_SIZE;i++) {
		if (spellMarkers.at(i)->IsPointCollision(mousePos)) {
			hoverTimers.at(i) += DELTA;
			if (hoverTimers.at(i) >= MARKER_HOVER_TIME) hoverTimers.at(i) = MARKER_HOVER_TIME;

			if (Input::Get()->IsKeyUp(VK_LBUTTON)) {
				selectedIndex = i;
			}

		}
		else {
			hoverTimers.at(i) -= DELTA;
			if (hoverTimers.at(i) < 0.0f) hoverTimers.at(i) = 0.0f;
		}

		MarkerMovePosition(spellMarkers.at(i), i);
		spellMarkers.at(i)->Update();
	}

	elementUI->Update();
	shapeUI->Update();
}

void SpellCustomUI::Render()
{
	if (!isActive)return;
	backGround->Render();

	for (int i = 0;i < SPELL_MARKERS_SIZE;i++) {
		if (i == selectedIndex) continue;
		spellMarkers.at(i)->Render();
	}


	pageLeft->Render();
	pageRight->Render();

	for (auto& slot : slots)
		slot->Render();

	for (auto& slot : sampleSlots)
		slot->Render();


	spellMarkers.at(selectedIndex)->Render();
	
	elementUI->Render();
	shapeUI->Render();
//	bookMarker->Render();

}

void SpellCustomUI::MarkerMovePosition(Button* marker,int index) {
	Vector2 targetPos = {10,-(index * 50.0f) };
	Vector2 movePos;
	movePos = GameMath::Lerp({0,-(index * 50.0f) }, targetPos, hoverTimers.at(index) / MARKER_HOVER_TIME);
	marker->SetLocalPosition(movePos);

}