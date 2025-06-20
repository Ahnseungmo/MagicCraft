#pragma once

class OptionButton : public RectCollider {

public:
	
	OptionButton(bool infinity = false);
	~OptionButton();
	void Update();
	void Render();
	void SetOption(Option* option) { this->option = option; option->SetParent(this); option->Update(); }

private:
	bool infinity = false;
	Quad* backGround;
	Quad* select;
	Option* option;
};