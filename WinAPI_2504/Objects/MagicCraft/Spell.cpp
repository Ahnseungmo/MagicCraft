#include "Framework.h"

Spell::Spell()
{
	isActive = false;
	image = new Quad(L"Resources/Textures/MagicCraft/SampleSpell.png");
	image->SetParent(this);
	image->UpdateWorld();
	
//	Clip* clip = new Clip("Arrow_Fire_begin.xml",);
/*
	LoadClip(Begin, "Resources/Textures/MagicCraft/Spell/Arrow/Fire/", "0begin.xml", false,2.0f);
	LoadClip(Moving, "Resources/Textures/MagicCraft/Spell/Arrow/Fire/", "1Moving.xml", true);
	LoadClip(End, "Resources/Textures/MagicCraft/Spell/Arrow/Fire/", "2End.xml", false, 2.0f);
	*/
	LoadClip();
	clips.at(Begin)->SetEvent((bind(&Spell::Fire, this)));
	clips.at(End)->SetEvent((bind(&Spell::Disappear, this)));

}

Spell::~Spell()
{
	//delete image;
	for (auto& clip : clips) {
		delete &clip;
	}
	clips.clear();

}

void Spell::Update()
{
	if (!isActive) return;
	if (state) {
		switch (state)
		{
		case Spell::Begin:

			break;
		case Spell::Moving:
			Translate(direction * speed * DELTA);
			break;
		case Spell::End:
			Translate(direction * 0);
			break;
		default:
			break;
		}
	}
	clips.at(state)->Update();
	UpdateWorld();
//	image->UpdateWorld();
}

void Spell::Render()
{
	if (!isActive) return;
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	clips.at(state)->Render();
//	image->Render();
	RectCollider::Render();

}

void Spell::Spawn(Vector2 pos,Vector2 dir,Vector2 size)
{
	SetSize(size);
	localRotation.z = atan2f(dir.y,dir.x);
	direction = dir;
	SetLocalPosition(pos);
	Translate(dir * Vector2(size.x / 2 * localScale.x, size.y / 2 * localScale.y));
	state = Begin;
	clips.at(state)->Play();
	isActive = true;
}

void Spell::Fire()
{
	state = Moving;
	clips.at(state)->Play();
}

void Spell::Hit()
{
	clips.at(state)->Stop();
	state = End;
	clips.at(state)->Play();
}

void Spell::Disappear()
{
	isActive = false;
}



/*

void Spell::LoadClip(State state, string path, string file, bool isLoop, float speed)
{
	vector<Frame*> frameData = DataManager::Get()->GetSpellFrames(shape,element);
	string filePath = path + (DataManager::Get()->SpellShapeToString.at(shape)) + "/" + (DataManager::Get()->SpellElementToString.at(element)) + "/";

//	for(auto)

	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	document->LoadFile((path + file).c_str());

	tinyxml2::XMLElement* atlas = document->FirstChildElement();
	string textureFile = path + atlas->Attribute("imagePath");

	vector<Frame*> frames;
	tinyxml2::XMLElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;
		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		wstring file = Utility::ToWString(textureFile);
		frames.push_back(new Frame(file, x, y, w, h));

		sprite = sprite->NextSiblingElement();
	}

	clips.insert(make_pair(state,new Clip(frames, isLoop, speed)));

	delete document;


}
*/

void Spell::LoadClip()
{
	vector<vector<Frame*>> frameDatas = DataManager::Get()->GetSpellFrames(shape, element);

	clips.insert(make_pair(Begin, new Clip(frameDatas.at(0), false, 2.0f)));
	clips.insert(make_pair(Moving, new Clip(frameDatas.at(1), false, 2.0f)));
	clips.insert(make_pair(End, new Clip(frameDatas.at(2), false, 2.0f)));


}