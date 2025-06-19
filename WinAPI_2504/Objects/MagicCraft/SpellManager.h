#pragma once


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
	float knockBack = 0.0f;
	float lifeTime = 1.0f;
	float speed = 0.0f;
//	Spell* nextSpell = nullptr;
};



class SpellManager : public Singleton<SpellManager>{
	friend class Singleton;
public:


	SpellManager();
	~SpellManager();


	static const unordered_map<Shape, string> ShapeToString;
	static const unordered_map<Element, string> ElementToString;
	static const unordered_map<string, Shape> StringToShape;
	static const unordered_map<string, Element> StringToElement;

	void LoadShapeDatas();
	void LoadElementDatas();

	void SetOptionShape(SpellOptionData* data, Shape shape);
	void SetOptionElement(SpellOptionData* data, Element element);
	void SetOptionDuplication(SpellOptionData* data);
	void SetOptionPierce(SpellOptionData* data);
	void SetOptionUpScale(SpellOptionData* data);
	void SetOptionHoming(SpellOptionData* data);
	void SetOptionReflect(SpellOptionData* data);


	SpellOptionData* GetSpellOptionData(int index) { return spellOptionDatas.at(index); }
	void SetSpellOptionData(int index, SpellOptionData* data) { spellOptionDatas.at(index) = data; }

private:
	const int SPELL_SLOT = 10;

	vector<SpellOptionData*> spellOptionDatas;

};