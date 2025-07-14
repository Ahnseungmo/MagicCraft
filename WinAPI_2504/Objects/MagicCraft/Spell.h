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

	void Spawn(Vector2 pos, Vector2 dir, SpellOptionData* data);

	void Fire();

	void Hit();

	void Disappear();

	void SetSpellOptionData(SpellOptionData* data);

	void LoadClip();


//	void LoadClip(State state, string path, string file, bool isLoop, float speed = 1.0f);

	State GetState() { return state; }

	float GetDamage() { return damage; }
//	void LoadClip(string path, string file, bool isLoop, float speed = 1.0f);
//	void Spawn(Vector2 pos, Vector2 dir);

//	void Spawn(Vector2 pos);

private:

	State state = Begin;
//	SpellOptionData* spellOptionData;
	SpellOptionData spellOptionData;

//	DataManager::SpellShape shape = DataManager::SpellShape::Arrow;
//	DataManager::SpellElement element = DataManager::SpellElement::Water;


	unordered_map<State, Clip*> clips;

	Vector2 direction = Vector2::Right();
	vector<Vector2> shapeSizes;
	const int BASE_SPEED = 400.0f;
	float speed= BASE_SPEED;
	float damage = 1;
	int pierce = 0;
	float lifeTime = 0;

	Transform* clipTransform;

};