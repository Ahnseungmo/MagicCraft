#include "Framework.h"

UIManager::UIManager()
{
	book = new SpellCustomUI();
	book->SetLocalPosition(CENTER);
//	book->SetZPos(0.000001);
	book->SetZPos(-0.3);

	book->UpdateWorld();
	mouseTransform = new Transform();
	book->SetActive(false);
	bookState = false;


	playerStateUI = new PlayerStateUI;
	playerStateUI->SetZPos(-0.32);
	playerStateUI->SetLocalPosition(100,700);

}

UIManager::~UIManager()
{
//	Singleton::Delete();
	delete book;
	delete mouseTransform;
	delete selectOption;
}

void UIManager::Update()
{


	mouseTransform->SetLocalPosition(mousePos);
	
	if (Input::Get()->IsKeyDown(VK_TAB)) {

		bookState = !bookState;
		if (!bookState) {
			int selectdIndex = book->GetSelectIndex();
			book->SetSpellSlotData(selectdIndex);
			book->CalSpellSlotData(selectdIndex);
		}
		UIManager::SetPause(bookState);
	}

	if (bookState) bookPositionTime += DELTA;
	else bookPositionTime -= DELTA;
	bookPositionTime = GameMath::Clamp(bookPositionTime,0.0f,BOOK_POSITION_TIMER);
	if (bookPositionTime <= 0) {
		book->SetActive(false);

	}
	else book->SetActive(true);

	Vector2 bookMovePos = GameMath::Lerp(bookPosition.at(0), bookPosition.at(1), bookPositionTime/ BOOK_POSITION_TIMER);
	book->SetLocalPosition(bookMovePos);
	mouseTransform->UpdateWorld();
	book->Update();


	if (Input::Get()->IsKeyUp(VK_LBUTTON)) SetSelectOption(nullptr);
	
	if (selectOption != nullptr) {
		selectOption->SetZPos(book->GetZPos() -0.004);
		selectOption->Update();
	}

	playerStateUI->Update();
}

void UIManager::Render()
{
	book->Render();
	if (selectOption != nullptr) selectOption->Render();

	playerStateUI->Render();
}
