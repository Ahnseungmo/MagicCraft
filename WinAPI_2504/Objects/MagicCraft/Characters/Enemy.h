#pragma once

class Enemy : public Character {
	


public:
	enum Mode {
		TRACE,
		PATROL
	};

	Enemy();
	~Enemy();

	void Update();

	bool HitCheck(Collider* collider);
	void Edit();


	void MovePatrol();
	void PathControl();
	void SetPath(const vector<Vector2>& path) { this->path = path; }
	void Attack();

	void LoadClip(State state, Direction direction, string path, string file, bool isLoop, float speed);
	void SetSpawner(Vector2 spawner) { this->spanwer = spawner; }


private:
	Mode mode = TRACE;
	Vector2 velocity;
	vector<Vector2> path;

	vector<Vector2> patrolPath;

	int power = 10;
	RectCollider* attackBox;

	float restTimer = 0;
	const float REST_TIME = 1.0f;

//	Transform* spawnPoint;
	Vector2 spanwer;


};