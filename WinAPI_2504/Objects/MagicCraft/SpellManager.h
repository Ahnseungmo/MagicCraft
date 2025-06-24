#pragma once





class SpellManager : public Singleton<SpellManager>{
	friend class Singleton;
public:


	SpellManager();
	~SpellManager();

	void Update();
	void Render();

	void Spawn(Vector2 pos, Vector2 dir, SpellOptionData* data);

	void HitCheck();


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
	const int SPELL_POOL = 50;

	vector<Spell*> spells;
	vector<SpellOptionData*> spellOptionDatas;

};