#pragma once

class UIManager : public Singleton<UIManager> {
	friend class Singleton;
public:
	UIManager();
	~UIManager();

	void Update();
	void Render();

private:

};