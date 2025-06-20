#pragma once

class SpellCustomUI : public RectCollider {

public:
	SpellCustomUI();
	~SpellCustomUI();

	void Update();
	void Render();


private:
	Quad* backGround;
	Quad* pageLeft;
	Quad* pageRight;

//	Quad* select;
	OptionButton* slot;
	OptionButton* slot2;

	Option* optionPieace;


	const int OPTION_BUTTON_ROW = 5;
	const int OPTION_BUTTON_COL = 3;

	vector<OptionButton*> slots;



};