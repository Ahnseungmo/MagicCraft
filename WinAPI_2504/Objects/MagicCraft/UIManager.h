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
	bool isPause = false;

	Option* selectOption = nullptr;
	Transform* mouseTransform;

	SpellCustomUI* book;

};