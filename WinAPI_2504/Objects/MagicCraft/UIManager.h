#pragma once

class UIManager : public Singleton<UIManager> {
	friend class Singleton;
public:
	UIManager();
	~UIManager();

	void Update();
	void Render();


	void SetSelectOption(Option* option) { this->selectOption = option;	if(selectOption) selectOption->SetParent(mouseTransform); }
	Option* GetSelectOption() { return selectOption; }

	void SetPause(bool isPause) { this->isPause = isPause; }
	bool IsPause() { return isPause; }
private:
	const float BOOK_POSITION_TIMER = 0.2f;
	bool isPause = false;
	bool bookState = false;

	Option* selectOption = nullptr;
	Transform* mouseTransform;

	SpellCustomUI* book;
	vector<Vector2> bookPosition = { CENTER - Vector2{0,700.0f}, {CENTER} };
	float bookPositionTime = 0;

};