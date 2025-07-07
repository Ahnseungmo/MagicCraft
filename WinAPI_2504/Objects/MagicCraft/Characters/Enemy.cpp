#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy()
{
	isActive = false;


}

Enemy::~Enemy()
{
	for (auto& clip : clips) {
		delete clip;
	}
	clips.clear();
}

void Enemy::Update()
{
	/*
	UpdateWorld();
	clips.at((int)dir)->Update();
	*/
	if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
		SetLocalPosition(mousePos + Environment::Get()->GetMainCamera()->GetGlobalPosition());
		UpdateWorld();
	}
	if (mode == TRACE) {
		PathControl();
	}
	Character::Update();
}

bool Enemy::HitCheck(Collider* collider) {
	if (!isActive) return false;
	if (!collider->IsActive()) return false;

	if (collider->IsCircleCollision(this)) {

		return true;
	}

	return false;
}


void Enemy::Edit()
{

	ImGui::DragFloat("hp", &hp);

}

void Enemy::MovePatrol()
{

	int start = map->CalPosToIndex(GetGlobalPosition());


	int end = map->CalPosToIndex(player->GetGlobalPosition());


	//			enemy->SetPath(aStar->GetPath(start, end,2));

	patrolPath = aStar->GetPathToTarget(start, end, 1);
}

void Enemy::PathControl()
{
	if (path.empty()) {
		state = Idle;
		return;
	}
	state = Run;

	Vector2 destPos = path.back();

	velocity = destPos - localPosition;

	if (velocity.Magnitude() < 1.0f)
	{
		path.pop_back();
	}
	else
	{
		velocity.Normalize();
	}

	float angle = atan2(velocity.y, velocity.x);
	if (angle >= -PI / 4 && angle < PI / 4) {
		dir = Right;
	}
	else if (angle >= PI / 4 && angle < 3 * PI / 4) {
		dir = Up;
	}
	else if (angle >= -3 * PI / 4 && angle < -PI / 4) {
		dir = Down;
	}
	else {
		dir = Left;
	}

	Translate(velocity * speed * DELTA);
}

void Enemy::Attack()
{
	Player* player = EnemyManager::Get()->GetPlayer();
	if (attackBox->IsCircleCollision(player)) {
		player->Hit(power);
	}

}

void Enemy::LoadClip(State state, Direction direction, string path, string file, bool isLoop, float speed)
{
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

//	clips.push_back(new Clip(frames, isLoop, speed));
//	motionClips.insert(make_pair(state, make_pair(direction, new Clip(frames, isLoop, speed))));
	motionClips[state][direction] = new Clip(frames, isLoop, speed);
	delete document;
}

