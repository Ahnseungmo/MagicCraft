#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy()
{
	isActive = false;
	string path = "Resources/Textures/MagicCraft/Character/Player/";
	LoadClip(path, "Move_Up.xml", true, 1.0f);
	LoadClip(path, "Move_Right.xml", true, 1.0f);
	LoadClip(path, "Move_Down.xml", true, 1.0f);
	LoadClip(path, "Move_Left.xml", true, 1.0f);

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

void Enemy::PathControl()
{
	if (path.empty())
		return;

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

//]	localRotation.z = atan2(velocity.y, velocity.x);
	Translate(velocity * speed * DELTA);
}
