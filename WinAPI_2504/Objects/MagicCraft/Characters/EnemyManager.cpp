#include "Framework.h"

EnemyManager::EnemyManager()
{
	/*
	enemys.reserve(ENEMY_POOL);
	for (int i = 0;i < ENEMY_POOL;i++) {
		enemys.push_back(new Plant1());
	}
	*/
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
		/*
		if (search) {
			int start = gameMap->CalPosToIndex(enemy->GetGlobalPosition());
			int end = gameMap->CalPosToIndex(player->GetGlobalPosition());
			
//			enemy->SetPath(aStar->GetPath(start, end,2));
			enemy->SetPath(aStar->GetPathToTarget(start, end, 1));
			
		}
		*/
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
void EnemyManager::SetEnemys()
{
	spawners.clear();
	for (auto& spawnPoint : gameMap->GetEnemySpanwer()) {
		Vector2 pos = gameMap->GetFloors().at(gameMap->CalTilePosToIndex(spawnPoint))->GetGlobalPosition();
//		Vector2 pos = spawnPoint * 32;
		spawners.push_back(pos);
	}

	enemys.reserve(spawners.size());


	for (auto& spawner : spawners) {
		
		float dis[5];
		float ldis;
		int index = 0;
		for (int i = 0;i < 5;i++) {
			dis[i] = Vector2::Distance(spawner, gameMap->GetFloors().at(gameMap->CalTilePosToIndex(gameMap->GetBiomeBassTilePos().at(i)))->GetGlobalPosition());
		}
		ldis = dis[0];
		for (int i = 1;i < 5;i++) {
			if (ldis >= dis[i]) {
				index = i;
				ldis = dis[i];
			}
		}

		switch (index) {
		case 0:
			enemys.push_back(new Plant1());

			break;
		case 1:
			enemys.push_back(new Plant2());
			break;

		case 2:
			enemys.push_back(new Plant3());
			break;
		case 3:
			enemys.push_back(new Orc1());
			break;
		case 4:
			enemys.push_back(new Orc2());
			break;


		}



		enemys.back()->SetSpawner(spawner);
		enemys.back()->SetLocalPosition(spawner);
//		enemys.back()->UpdateWorld();
		enemys.back()->SetActive(true);
	}

}
/*
vector<Vector2> EnemyManager::Compare(vector<Vector2> enemys) {


}
*/