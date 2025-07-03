#pragma once

class Character : public CircleCollider{


public:
	enum Direction {
		Up,
		Right,
		Down,
		Left
	};
	Character();
	~Character();

	void Update();
	void Render();
	void Spawn(Vector2 pos);

	bool Hit(float damage);

	void LoadClip(string path, string file, bool isLoop, float speed);

	void UpdateWorld();

	void TileCheck();

	void SetMap(GameMap* map) { this->map = map; }
protected:

	float hp=100;

	const float HIT_INTERVAL = 0.3f;
	float hitTimer = HIT_INTERVAL;

	Direction dir = Down;
	Vector2 direction = Vector2::Down();
	vector<Clip*> clips;


	float speed = 100;
	bool isMove = false;

	GameMap* map;

};