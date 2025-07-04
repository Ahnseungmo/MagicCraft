#pragma once

class OptionButton : public RectCollider {

public:
	
	OptionButton(bool infinity = false);
	~OptionButton();
	void Update();
	void Render();
	void SetOption(Option* option) { this->option = option; option->SetParent(this); option->SetZPos(-0.001); option->Update(); }
	Option* GetOption() { return option; }
	void DeleteOption() {

		option = nullptr;
	}
	bool GetInfinity() { return false; }
	void SetInfinity(bool infinity) { this->infinity = infinity; }
	void SetClickAble(bool isClickAble) { this->isClickAble = isClickAble; }
	bool GetClickAble() { return isClickAble; }

private:
	bool isClickAble = false;
	bool infinity = false;
	Quad* backGround;
	Quad* select;
	Option* option;
};