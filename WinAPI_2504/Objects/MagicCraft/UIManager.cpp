#include "Framework.h"

UIManager::UIManager()
{
	book = new SpellCustomUI();
	book->SetLocalPosition(CENTER);
	book->UpdateWorld();
	mouseTransform = new Transform();
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
		int state = book->IsActive();
		book->SetActive((++state) % 2);
	}



	mouseTransform->UpdateWorld();
	book->Update();


	if (Input::Get()->IsKeyUp(VK_LBUTTON)) SetSelectOption(nullptr);

	if (selectOption != nullptr) selectOption->Update();
}

void UIManager::Render()
{
	book->Render();
	if (selectOption != nullptr) selectOption->Render();
}
