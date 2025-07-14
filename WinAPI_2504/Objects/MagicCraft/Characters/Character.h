#pragma once

class Character : public CircleCollider{


public:
	enum Direction {
		Up = 0,
		Right,
		Down,
		Left
	};

	enum State {
		Idle = 0,
		Walk,
		Run,
		ATTACK,
		Hurt,
		Death
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
	void SetAStar(MapAStar* aStar) { this->aStar = aStar; }

	float GetHp() { return hp; }
	float GetHpMax() { return hpMax; }
protected:

	float hp=100;
	float hpMax = 100;
	const float HIT_INTERVAL = 0.3f;
	float hitTimer = HIT_INTERVAL;

	Direction dir = Down;
	State state = Idle;

	Vector2 direction = Vector2::Down();
	vector<Clip*> clips;

	unordered_map<State, unordered_map<Direction,Clip*>> motionClips;
	Transform* clipTransform;

	float speed = 100;
	bool isMove = false;

	GameMap* map;
	MapAStar* aStar;

};