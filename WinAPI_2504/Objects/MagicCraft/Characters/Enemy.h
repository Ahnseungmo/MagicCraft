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

	void PathControl();
	void SetPath(const vector<Vector2>& path) { this->path = path; }

private:
	Mode mode = TRACE;
	Vector2 velocity;
	vector<Vector2> path;

};