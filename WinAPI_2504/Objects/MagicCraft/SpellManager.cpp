#include "Framework.h"



SpellManager::SpellManager()
{
	spellOptionDatas.reserve(SPELL_SLOT);
	for (int i = 0;i < SPELL_SLOT;i++) {
		spellOptionDatas.push_back(new SpellOptionData());
	}
	spells.reserve(SPELL_POOL);
	for (int i = 0; i < SPELL_POOL; i++) {
		spells.push_back(new Spell());
	}

}

SpellManager::~SpellManager()
{
	for (auto& data : spellOptionDatas) {
		delete data;
	}
	spellOptionDatas.clear();

	for (auto& spell : spells) {
		delete spell;
	}
	spells.clear();

}

void SpellManager::Update() {
	for (auto& spell : spells) {
		spell->Update();
	}

}

void SpellManager::Render() {
	for (auto& spell : spells) {
		spell->Render();
	}


}
void SpellManager::Spawn(Vector2 pos, Vector2 dir, SpellOptionData* data) {

	for (auto& spell : spells) {
		if (!spell->IsActive()) {

			spell->Spawn(pos,dir,data);
			return;
		}
	}

}
void SpellManager::HitCheck() {
	for (auto& spell : spells) {
		if (spell->IsActive()) {

			EnemyManager::Get()->HitCheck(spell);
		}
	}
}



const unordered_map<Shape, string> SpellManager::ShapeToString{
	{Shape::Arrow, "Arrow"},
	{Shape::Ball, "Ball"},
	{Shape::Lay, "Lay"},
	{Shape::Knife, "Knife"},
	{Shape::Floor, "Floor" }

};
const unordered_map<Element, string> SpellManager::ElementToString{
	{Element::Fire, "Fire"},
	{Element::Water, "Water"},
	{Element::Ice, "Ice"},
	{Element::Tunder, "Tunder"},
	{Element::Earth, "Earth"}
};

const unordered_map<string,Shape> SpellManager::StringToShape{
	{"Arrow", Shape::Arrow},
	{"Ball", Shape::Ball},
	{"Lay", Shape::Lay},
	{"Knife", Shape::Knife},
	{"Floor", Shape::Floor}
};

const unordered_map<string, Element> SpellManager::StringToElement{
	{"Fire", Element::Fire},
	{"Water", Element::Water},
	{"Ice", Element::Ice},
	{"Tunder", Element::Tunder},
	{"Dirt", Element::Earth}
};


void SpellManager::SetOptionShape(SpellOptionData* data, Shape shape)
{
	switch (shape)
	{
	case Arrow:
		data->speed = 1.0f;
		data->lifeTime = 1.0f;
		data->power = 1.0f;
		data->cost = 10;
		break;
	case Ball:
		data->speed = 0.8f;
		data->lifeTime = 1;
		data->power = 2.0f;
		data->cost = 20;
		break;
	case Knife:
		data->speed = 1.0f;
		data->lifeTime = 1;
		data->power = 2.0f;
		data->cost = 20;
		data->pierce = -1;
		break;
	case Lay:
		data->speed = -1.0f;
		data->lifeTime = -1.0f;
		data->power = 0.3;
		data->cost = 10;
		break;
	case Floor:
		data->speed = 0;
		data->lifeTime = 4.0f;
		data->power = 0.5;
		data->cost = 10;
		data->pierce = -1;
		break;
	default:
		break;
	}
}
void SpellManager::SetOptionElement(SpellOptionData* data, Element element)
{
	data->element = element;
	switch (element)
	{
	case Fire:
		break;
	case Water:
		data->knockBack = 0.5f;
		break;
	case Ice:
		break;
	case Tunder:
		data->speed *= 5.0f;
		break;
	case Earth:
		data->speed *= 0.8f;
		data->knockBack = 1.0f;
		break;

	default:
		break;
	}
}
void SpellManager::SetOptionDuplication(SpellOptionData* data) {
	data->duplication += 1;
	data->cost += 1;
}

void SpellManager::SetOptionPierce(SpellOptionData* data)
{
	if (data->pierce >= 0) data->pierce += 1;
	data->cost += 1;
}

void SpellManager::SetOptionUpScale(SpellOptionData* data)
{
	data->scale += 1;
	data->cost += 1;
}

void SpellManager::SetOptionHoming(SpellOptionData* data)
{
	data->homing += 0.5f;
//	if (data->homing >= 1.0f) data->homing = 1.0f;
	data->cost += 1;
}

void SpellManager::SetOptionReflect(SpellOptionData* data)
{
	data->reflect += 1;
	data->cost += 1;
}
