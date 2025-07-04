#include "Framework.h"

EnemyManager::EnemyManager()
{
	enemys.reserve(ENEMY_POOL);
	for (int i = 0;i < ENEMY_POOL;i++) {
		enemys.push_back(new Enemy());
	}
}

EnemyManager::~EnemyManager()
{
	for (auto& enemy : enemys) {
		delete enemy;
	}
	enemys.clear();
}

void EnemyManager::Update()
{
	bool search = false;
	NodeSearchTimer += DELTA;
	if (NodeSearchTimer >= NODE_SEARCH_TIME) {
		NodeSearchTimer -= NODE_SEARCH_TIME;
		search = true;
	}

	for (auto& enemy : enemys) {
		if (!enemy->IsActive()) continue;
		if (search) {
			/*
			int start = aStar->FindCloseNode(enemy->GetGlobalPosition());
			int end = aStar->FindCloseNode(player->GetGlobalPosition());

			findStart = start;
			findEnd = end;
			*/
			int start = gameMap->CalPosToIndex(enemy->GetGlobalPosition());
			int end = gameMap->CalPosToIndex(player->GetGlobalPosition());
			
//			enemy->SetPath(aStar->GetPath(start, end,2));
			enemy->SetPath(aStar->GetPathToTarget(start, end, 1));
			
		}

		enemy->Update();
	}
}

void EnemyManager::Render()
{
	for (auto& enemy : enemys) {
		enemy->Render();
	}
}

void EnemyManager::Spawn(Vector2 pos)
{
	for (auto& enemy : enemys) {
		if (!enemy->IsActive()) {
			enemy->Spawn(pos);
			return;
		}
	}

}

void EnemyManager::HitCheck(Spell* spell) {
	for (auto& enemy : enemys) {
		if (enemy->HitCheck((Collider*)spell)) {
			if (enemy->Hit(spell->GetDamage())) {

				spell->Hit();


			}

		}
	}

}


void EnemyManager::Edit() {


	for (auto& enemy : enemys) {
		if (enemy->IsActive()) {
			enemy->Edit();
		}
	}
}



Enemy* EnemyManager::nearEnemy(Vector2 pos)
{
	bool isFirst = true;
	Enemy* nearEnemy = nullptr;
	float minDistance,temp;

	for (auto& enemy : enemys) {
		if (enemy->IsActive()) {
			if (isFirst) {
				isFirst = false;
				minDistance = Vector2::Distance(enemy->GetGlobalPosition(), pos);
				nearEnemy = enemy;
			}
			else {
				temp = Vector2::Distance(enemy->GetGlobalPosition(), pos);
				if (minDistance > temp) nearEnemy = enemy;
			}
		}
	}
	return nearEnemy;

}
/*
vector<Vector2> EnemyManager::Compare(vector<Vector2> enemys) {


}
*/