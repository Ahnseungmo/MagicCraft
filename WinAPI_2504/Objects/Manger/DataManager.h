#pragma once

struct ItemData
{
	enum Type
	{
		Weapon = 1, Armor, Potion
	};

	int key;
	string name;
	string explane;
	int price;
	int value;
	Type type;
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
	float knockBack = 0.0f;
	float lifeTime = 1.0f;
	float speed = 0.0f;
	//	Spell* nextSpell = nullptr;

//	vector<Option*> options;

};

class DataManager : public Singleton<DataManager>
{
	friend class Singleton;

private:
	DataManager();
	~DataManager();



public:

	void LoadData(const string& fileName);

	vector<string> GetSubdirectories(const string& path);

	void LoadFrames(string path);
	
	ItemData GetItem(int key) { return itemDatas[key]; }
	int GetItemCount() { return itemDatas.size(); }
//	vector<vector<Frame*>> GetSpellFrames(SpellShape shape, SpellElement element) { return spellFrames.at(shape).at(element); }
	vector<vector<Frame*>> GetSpellFrames(Shape shape, Element element) { return spellFrames.at(shape).at(element); }

private:
	unordered_map<int, ItemData> itemDatas;
//	unordered_map<SpellShape, unordered_map<SpellElement, vector<vector<Frame*>>>> spellFrames;
	unordered_map<Shape, unordered_map<Element, vector<vector<Frame*>>>> spellFrames;

	Shape shape;
//	unordered_map<string,
};

