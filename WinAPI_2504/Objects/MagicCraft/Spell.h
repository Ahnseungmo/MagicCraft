#pragma once

class Spell : public RectCollider {

public:
	Spell();
	~Spell();

	void Update();
	void Render();

	void Spawn(Vector2 pos, Vector2 dir, Vector2 size);

//	void Spawn(Vector2 pos, Vector2 dir);

//	void Spawn(Vector2 pos);

private:
	Quad* image;
	Vector2 direction = Vector2::Right();
	float speed=100;

};