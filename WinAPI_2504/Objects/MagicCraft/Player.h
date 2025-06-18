#pragma once

class Player : public CircleCollider {


public:
	enum Direction {
		Up,
		Right,
		Down,
		Left
	};
	Player();
	~Player();

	void Update();
	void Render();

	void LoadClip(string path, string file, bool isLoop, float speed);

	void Edit();

private:
	Direction dir = Down;
	Vector2 direction = Vector2::Down();
	vector<Clip*> clips;
	float speed = 100;
	bool isMove = false;


};