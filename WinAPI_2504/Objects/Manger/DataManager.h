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


class DataManager : public Singleton<DataManager>
{
	friend class Singleton;

private:
	DataManager();
	~DataManager();



public:

	enum SpellShape {
		Arrow,
		Ball,
		Lance,
		Knife
	};
	enum SpellElement {
		Fire,
		Water,
		Ice,
		Tunder,
		Dirt
	};

	void LoadData(const string& fileName);

	vector<string> GetSubdirectories(const string& path);

	void LoadFrames(string path);
	
	ItemData GetItem(int key) { return itemDatas[key]; }
	int GetItemCount() { return itemDatas.size(); }
	vector<vector<Frame*>> GetSpellFrames(SpellShape shape, SpellElement element) { return spellFrames.at(shape).at(element); }
	static const std::unordered_map<SpellShape, std::string> SpellShapeToString;
	static const std::unordered_map<SpellElement, std::string> SpellElementToString;
	static const std::unordered_map<std::string, SpellShape> StringToSpellShape;
	static const std::unordered_map<std::string, SpellElement> StringToSpellElement;
private:
	unordered_map<int, ItemData> itemDatas;
	unordered_map<SpellShape, unordered_map<SpellElement, vector<vector<Frame*>>>> spellFrames;


//	unordered_map<string,
};

