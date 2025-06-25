#include "Framework.h"

Spell::Spell()
{

	isActive = false;

//	Clip* clip = new Clip("Arrow_Fire_begin.xml",);
/*
	LoadClip(Begin, "Resources/Textures/MagicCraft/Spell/Arrow/Fire/", "0begin.xml", false,2.0f);
	LoadClip(Moving, "Resources/Textures/MagicCraft/Spell/Arrow/Fire/", "1Moving.xml", true);
	LoadClip(End, "Resources/Textures/MagicCraft/Spell/Arrow/Fire/", "2End.xml", false, 2.0f);
	*/
//	LoadClip();

	shapeSizes.resize(Shape::ShapeSize);
	for (int i = 0; i < Shape::ShapeSize;i++) {
		switch (i)
		{
		case Arrow:
			shapeSizes.at(i) = Vector2(32, 16);
			break;
		case Ball:
			shapeSizes.at(i) = Vector2(32, 32);
			break;
		case Blade:
			shapeSizes.at(i) = Vector2(16, 32);
			break;
		case Lay:
			shapeSizes.at(i) = Vector2(320, 16);
			break;
		case Floor:
			shapeSizes.at(i) = Vector2(64, 64);
			break;

		default:
			break;
		}
	}



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

			if (spellOptionData.homing != 0) {
				Enemy* target = EnemyManager::Get()->nearEnemy(GetGlobalPosition());
				if (target != nullptr) {
					Vector2 toTarget = target->GetGlobalPosition() - GetGlobalPosition();
					toTarget.Normalize();

					float currentAngle = atan2f(direction.y, direction.x);
					float targetAngle = atan2f(toTarget.y, toTarget.x);

					float deltaAngle = targetAngle - currentAngle;

					// 보정: -PI ~ PI로 유지
					if (deltaAngle > PI)
						deltaAngle -= 2 * PI;
					else if (deltaAngle < -PI)
						deltaAngle += 2 * PI;

					// 회전 제한
					float maxTurnAngle = spellOptionData.homing * PI * DELTA;
					float clampedDelta = GameMath::Clamp(deltaAngle, -maxTurnAngle, maxTurnAngle);

					float newAngle = currentAngle + clampedDelta;

					direction = Vector2(cosf(newAngle), sinf(newAngle));
					direction.Normalize();

					localRotation.z = newAngle;
				}

			}


			Translate(direction * speed * DELTA);
			break;
		case Spell::End:
			Translate(direction * 0);
			break;
		default:
			break;
		}
	}
	if(state == Moving) lifeTime += DELTA;
	if (lifeTime > spellOptionData.lifeTime)
	{
		lifeTime = 0;
		clips.at(state)->Stop();
		state = End;
		clips.at(state)->Play();
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
/*
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
*/

void Spell::Spawn(Vector2 pos, Vector2 dir, SpellOptionData* data)
{
	SetSpellOptionData(data);
	LoadClip();
	damage = spellOptionData.power;
	pierce = spellOptionData.pierce;

	SetLocalPosition(pos);
	SetSize(shapeSizes.at(spellOptionData.shape));
	SetLocalScale(spellOptionData.scale, spellOptionData.scale);
	localRotation.z = atan2f(dir.y, dir.x);
	direction = dir;
	UpdateWorld();


	Translate(dir * Size().Magnitude() * 0.5);
	state = Begin;
	clips.at(state)->Play();
	isActive = true;
	lifeTime = 0;
	speed = BASE_SPEED * spellOptionData.speed;
}

void Spell::Fire()
{
	state = Moving;
	clips.at(state)->Play();
}

void Spell::Hit()
{
	if (pierce == 0) {
		clips.at(state)->Stop();
		state = End;
		clips.at(state)->Play();
	}
	pierce--;
	
}

void Spell::Disappear()
{
	isActive = false;
}

void Spell::SetSpellOptionData(SpellOptionData* data) {
	spellOptionData.shape = data->shape;
	spellOptionData.element = data->element;
	spellOptionData.cost = data->cost;

	spellOptionData.duplication = data->duplication;
	spellOptionData.homing = data->homing;
	spellOptionData.knockBack = data->knockBack;
	spellOptionData.lifeTime = data->lifeTime;
	spellOptionData.pierce = data->pierce;
	spellOptionData.power = data->power;
	spellOptionData.reflect = data->reflect;
	spellOptionData.scale = data->scale;
	spellOptionData.speed = data->speed;
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
	Shape shape = spellOptionData.shape;
	Element element = spellOptionData.element;

	vector<vector<Frame*>> frameDatas = DataManager::Get()->GetSpellFrames(shape, element);

	for (auto& clip : clips) {
		delete clip.second;
	}
	clips.clear();

	clips.insert(make_pair(Begin, new Clip(frameDatas.at(0), false, 2.0f)));
	clips.insert(make_pair(Moving, new Clip(frameDatas.at(1), true, 2.0f)));
	clips.insert(make_pair(End, new Clip(frameDatas.at(2), false, 2.0f)));

	clips.at(Begin)->SetEvent((bind(&Spell::Fire, this)));
	clips.at(End)->SetEvent((bind(&Spell::Disappear, this)));

}
