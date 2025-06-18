#pragma once
enum Shape {
	Arrow,
	Ball,
	Knife,
	Lay,
	Floor,
	ShapeSize
};

enum Element {
	Fire,
	Water,
	Ice,
	Tunder,
	Earth,
	ElementSize
};


class ShapeData {
public:

};

class ElementData {
public:

};

class SpellOptionData {
public:
	Shape shape = Arrow;
	Element element = Fire;

	int cost = 0;
	int duplication = 0;
	int pierce = 0;
	int reflect = 0;
	float power = 0.0f;
	float scale = 1.0f;
	float homing = 0.0f;
	float nockBack = 0.0f;
	float lifeTime = 1.0f;
	float speed = 0.0f;
	Spell* nextSpell = nullptr;
};



class SpellManager : public Singleton<SpellManager>{
	friend class Singleton;
public:


	SpellManager();
	~SpellManager();


	void LoadShapeDatas();
	void LoadElementDatas();

private:
	const int SPELL_SLOT = 10;
	unordered_map<Shape, ShapeData*> shapeDatas;
	unordered_map<Element, ElementData*> elementDatas;

	vector<SpellOptionData*> spellOptionDatas;

};