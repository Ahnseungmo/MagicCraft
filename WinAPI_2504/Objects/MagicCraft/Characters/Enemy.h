#pragma once

class Enemy : public Character {


public:

	Enemy();
	~Enemy();

	void Update();

	bool HitCheck(Collider* collider);
	void Edit();

private:



};