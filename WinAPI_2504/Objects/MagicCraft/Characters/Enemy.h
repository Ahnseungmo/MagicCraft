#pragma once

class Enemy : public Character {
	


public:
	enum Mode {
		TRACE,
		PATROL,
		ATTACKING,
		REST,

	};

	Enemy();
	~Enemy();

	void Update();
	void Render();

	bool HitCheck(Collider* collider);
	void Edit();


	void MovePatrol();
	void PathControl(vector<Vector2>& path, float speed);
//	void PathControl();
	void SetPath(const vector<Vector2>& path) { this->path = path; }
	void Attack();

	void EndAttack();

	void LoadClip(State state, Direction direction, string path, string file, bool isLoop, float speed);
	void SetSpawner(Vector2 spawner) { this->spanwer = spawner; }


private:
	Mode mode = TRACE;
	Vector2 velocity;

	vector<Vector2> path;
	vector<Vector2> patrolPath;

	const int PATROL_RANGE = 5;

	const float FIND_PLAYER_TIME = 0.2;
	float findPlayerTimer = FIND_PLAYER_TIME;

	const float IDLE_TIME = 1.0f;
	float idleTimer = IDLE_TIME;

	int power = 10;
	RectCollider* attackBox;

	float restTimer = 0;
	const float REST_TIME = 1.0f;

//	Transform* spawnPoint;
	Vector2 spanwer = {0,0};

protected:
	ValueBar* hpBar;
};