#include "Framework.h"

OptionButton::OptionButton(bool infinity) : RectCollider({60,60}), infinity(infinity)
{
	backGround = new Quad(L"Resources/Textures/MagicCraft/UI/Book/Slot.png");
	select = new Quad(L"Resources/Textures/MagicCraft/UI/Book/Select.png");

	backGround->SetParent(this);
	backGround->UpdateWorld();

	select->SetParent(this);
	select->UpdateWorld();
	select->SetActive(false);
}

OptionButton::~OptionButton()
{
	delete backGround;
	delete select;
}

void OptionButton::Update()
{

	if (IsPointCollision(mousePos)) {
		select->SetActive(true);
		if (Input::Get()->IsKeyDown(VK_LBUTTON) && option) {
			UIManager::Get()->SetSelectOption(new Option(option));

			if (!infinity) option = nullptr;
		}
		if (Input::Get()->IsKeyUp(VK_LBUTTON)) {

			if (!infinity) {
				delete option;
				Option* selOption = UIManager::Get()->GetSelectOption();
				if (selOption != nullptr) SetOption(new Option(selOption));


			}

		}
	}
	else {
		select->SetActive(false);
	}
	



	UpdateWorld();
	backGround->UpdateWorld();
	select->UpdateWorld();
	if(option!=nullptr) option->Update();

}

void OptionButton::Render()
{
	backGround->Render();
	if(select->IsActive())	select->Render();
	if(option!=nullptr) option->Render();

}
