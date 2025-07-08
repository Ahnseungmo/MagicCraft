#pragma once

class EnemyManager : public Singleton<EnemyManager> {
	friend class Singleton; 

public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Render();
	void Spawn(Vector2 pos);

	void HitCheck(Spell* spell);

	void Edit();

	Enemy* nearEnemy(Vector2 pos);
	void SetPlayer(Player* player) { this->player = player; }
	Player* GetPlayer() { return player; }

	void SetGameMap(GameMap* map) {
		this->gameMap = map; 
		for (auto& enemy : enemys) {
			enemy->SetMap(gameMap);
		}

	}

	void SetAStar(MapAStar* aStar) {
		this->aStar = aStar;
		for (auto& enemy : enemys) {
			enemy->SetAStar(aStar);
		}

	}
	void InsertSpawners(Vector2 pos) {
		spawners.push_back(pos);
	}

	void SetEnemys();

private:
	const int ENEMY_POOL = 10;
	const float NODE_SEARCH_TIME = 0.2;
	vector<Enemy*> enemys;
	float NodeSearchTimer = 0;
	Player* player;
	MapAStar* aStar;
	GameMap* gameMap;

	int calStart;
	int calEnd;

	int findStart;
	int findEnd;

	vector<Vector2> spawners;

};