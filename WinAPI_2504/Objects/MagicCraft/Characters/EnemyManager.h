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
	
private:
	const int ENEMY_POOL = 10;
	vector<Enemy*> enemys;
};