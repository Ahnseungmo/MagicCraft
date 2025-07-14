#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy()
{
	isActive = false;

	hpBar = new ValueBar(L"Resources/Textures/MagicCraft/Character/Enemys/ValueRed_32x8.png");
	hpBar->SetParent(this);
	hpBar->SetLocalPosition(0,50);


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
	/*
	//µð¹ö±ë¿ë ÁÂÇ¥ÀÌµ¿ 
	if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
		Vector2 pos = mousePos + Environment::Get()->GetMainCamera()->GetGlobalPosition();
		SetLocalPosition(pos);
		spanwer = pos;
		mode = PATROL;
		patrolPath.clear();
		UpdateWorld();
	}
	*/
	/*
	Player* player = EnemyManager::Get()->GetPlayer();
	float distance = Vector2::Distance(GetGlobalPosition(), player->GetGlobalPosition());

	findPlayerTimer += DELTA;
	int start = map->CalPosToIndex(GetGlobalPosition());
	int end;

	if (idleTimer >= IDLE_TIME) {
		if (findPlayerTimer >= FIND_PLAYER_TIME) {
			mode = PATROL;
			findPlayerTimer = 0;
			end = map->CalPosToIndex(player->GetGlobalPosition());
			path = aStar->GetPathToTarget(start, end, 1);

		}

		if (spanwer.x == 0 && spanwer.y == 0) {


		}
		else if (patrolPath.size() <= 0) {
			Vector2 pos = map->CalPosToTilePos(spanwer);
			while (true) {
				Vector2 searchPos = Vector2{ (float)(rand() % PATROL_RANGE),(float)(rand() % PATROL_RANGE) };
				Vector2 targetPos = pos + searchPos - Vector2(ceilf(PATROL_RANGE * 0.5), ceilf(PATROL_RANGE * 0.5));
				int index = map->CalTilePosToIndex(targetPos);
				if (map->GetTileData(index)->state == Tile::FLOOR) {
					end = index;
					patrolPath = aStar->GetPathToTarget(start, end, 1);
					if(patrolPath.size()< PATROL_RANGE) break;
				}
			}

		}

	}
	else {
		idleTimer += DELTA;
		state = Idle;
	}

	if (mode != ATTACKING && mode != REST) {

		if (distance < 32 * 5) mode = TRACE;
		if (distance >= 32 * 5) mode = PATROL;
		if (path.size() <= 1 && distance < 30) {
			mode = ATTACKING;
		}

	}

	switch (mode)
	{
	case Enemy::TRACE:
		state = Run;
		PathControl(path,speed);
		break;
	case Enemy::PATROL:
		state = Walk;
		PathControl(patrolPath,speed * 0.5);
		break;
	case Enemy::ATTACKING:
		if (state != ATTACK) {
			state = ATTACK;
			motionClips[ATTACK][dir]->Play();
		}

		break;


	case Enemy::REST: 
		idleTimer += DELTA;
		if (state != Idle) {
			state = Idle;

		}
		break;


	default:
		break;
	}


	Character::Update();
	
	*/

	


	Player* player = EnemyManager::Get()->GetPlayer();
	float distance = Vector2::Distance(GetGlobalPosition(), player->GetGlobalPosition());
	Vector2 spawnerPos = map->CalPosToTilePos(spanwer);

	int start = map->CalPosToIndex(GetGlobalPosition());
	int end;

	switch (mode)
	{
	case Enemy::TRACE:

		state = Run;

		findPlayerTimer += DELTA;
		if (findPlayerTimer >= FIND_PLAYER_TIME) {
//			mode = PATROL;
			findPlayerTimer = 0;
			end = map->CalPosToIndex(player->GetGlobalPosition());
			path = aStar->GetPathToTarget(start, end, 1);

		}

		PathControl(path, speed);

		if (distance >= 32 * 5) mode = PATROL;
		if (path.size() <= 1 && distance < 30) {
			mode = ATTACKING;
		}

		break;
	case Enemy::PATROL:


		if (spanwer.x == 0 && spanwer.y == 0) {


		}
		else if (patrolPath.size() <= 0) {
			do{
				Vector2 searchPos = Vector2{ (float)(rand() % PATROL_RANGE),(float)(rand() % PATROL_RANGE) };
				Vector2 targetPos = spawnerPos + searchPos - Vector2(ceilf(PATROL_RANGE * 0.5), ceilf(PATROL_RANGE * 0.5));
				int index = map->CalTilePosToIndex(targetPos);
				if (map->GetTileData(index)->state == Tile::FLOOR) {
					end = index;
					patrolPath = aStar->GetPathToTarget(start, end, 1);
				}
				else {
					continue;
				}
			} while (patrolPath.size() > PATROL_RANGE);
			mode = REST;
			idleTimer = 0;
		}
		else {
			state = Walk;
			PathControl(patrolPath, speed * 0.5);
		}




		if (distance < 32 * 5) mode = TRACE;

		break;

	case Enemy::ATTACKING:
		if (state != ATTACK) {
			state = ATTACK;
			motionClips[ATTACK][dir]->Play();
		}
		break;

	case Enemy::REST:
		if (state != Idle) {
			state = Idle;
		}
		idleTimer += DELTA;
		if (idleTimer >= IDLE_TIME) {
			mode = PATROL;
		}
		break;


	default:
		break;
	}

	Character::Update();
	
	hpBar->UpdateWorld();
//	hpBar->SetZPos(GetZPos());
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

	/*
	int end = map->CalPosToIndex(player->GetGlobalPosition());


	//			enemy->SetPath(aStar->GetPath(start, end,2));

	patrolPath = aStar->GetPathToTarget(start, end, 1);*/
}

void Enemy::PathControl(vector<Vector2>& path,float speed)
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

void Enemy::Render() {

	Character::Render();
/*
	worldBuffer->Set(hpBarTransform->GetWorld());
	worldBuffer->SetVS(0);

	*/
	hpBar->SetValue(hp / hpMax);
	hpBar->Render();

}
void Enemy::Attack()
{
	Player* player = EnemyManager::Get()->GetPlayer();
	if (attackBox->IsCircleCollision(player)) {
		player->Hit(power);
	}

}

void Enemy::EndAttack()
{
	mode = REST;
	idleTimer = 0;
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

