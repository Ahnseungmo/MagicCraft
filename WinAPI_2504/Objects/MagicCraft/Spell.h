#pragma once

class Spell : public RectCollider {

public:
	enum State {
		Begin,
		Moving,
		End
	};


	Spell();
	~Spell();

	void Update();
	void Render();

	void Spawn(Vector2 pos, Vector2 dir, Vector2 size);

	void Fire();

	void Hit();

	void Disappear();

	void LoadClip();

//	void LoadClip(State state, string path, string file, bool isLoop, float speed = 1.0f);

	State GetState() { return state; }
//	void LoadClip(string path, string file, bool isLoop, float speed = 1.0f);
//	void Spawn(Vector2 pos, Vector2 dir);

//	void Spawn(Vector2 pos);

private:

	State state = Begin;
	DataManager::SpellShape shape = DataManager::SpellShape::Arrow;
	DataManager::SpellElement element = DataManager::SpellElement::Fire;

	Quad* image;

	unordered_map<State, Clip*> clips;

	Vector2 direction = Vector2::Right();
	float speed=400;

};