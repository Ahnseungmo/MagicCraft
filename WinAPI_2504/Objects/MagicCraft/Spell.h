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

//	void Spawn(Vector2 pos, Vector2 dir, Vector2 size);

	void Spawn(Vector2 pos, Vector2 dir, Vector2 size, SpellOptionData* data);

	void Fire();

	void Hit();

	void Disappear();

	void LoadClip();

//	void LoadClip(State state, string path, string file, bool isLoop, float speed = 1.0f);

	State GetState() { return state; }

	int GetDamage() { return damage; }
//	void LoadClip(string path, string file, bool isLoop, float speed = 1.0f);
//	void Spawn(Vector2 pos, Vector2 dir);

//	void Spawn(Vector2 pos);

private:

	State state = Begin;
	SpellOptionData* spellOptionData;
//	DataManager::SpellShape shape = DataManager::SpellShape::Arrow;
//	DataManager::SpellElement element = DataManager::SpellElement::Water;


	unordered_map<State, Clip*> clips;

	Vector2 direction = Vector2::Right();
	vector<Vector2> shapeSizes;

	float speed=400;
	int damage = 1;
	int pierce = 0;
	float lifeTime = 0;


};