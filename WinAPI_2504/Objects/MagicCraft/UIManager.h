#pragma once

class UIManager : public Singleton<UIManager> {
	friend class Singleton;
public:
	UIManager();
	~UIManager();

	void Update();
	void Render();


	void SetSelectOption(Option* option) { this->selectOption = option; }
	Option* GetSelectOption() { return selectOption; }
private:

	Option* selectOption = nullptr;
};