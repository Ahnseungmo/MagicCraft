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
	void SetAStar(MapAStar* aStar) { this->aStar = aStar; }
	void SetGameMap(GameMap* map) { this->gameMap = map; }

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

};