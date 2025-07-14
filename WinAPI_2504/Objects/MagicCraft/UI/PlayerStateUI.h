#pragma once

class PlayerStateUI :public Transform{

public:
	PlayerStateUI();
	~PlayerStateUI();


	void Update();
	void Render();

	void SetPlayer(Player* player) { this->player = player; }
	Player* GetPlayer() { return player; }
private:

	Quad* hpBack;
	Quad* mpBack;
	ValueBar* hpBar;
	ValueBar* mpBar;

	Player* player;
};