#pragma once

class Tank : public RectCollider
{
private:
	enum AnimState
	{
		Idle, Move
	};

	const float SPEED = 200.0f;

public:
	Tank();
	~Tank();
	
	void Update();
	void Render();

	void SetTileMap(TileMap* tileMap) { this->tileMap = tileMap; }

	void SetPath(const vector<Vector2>& path) { this->path = path; }

private:
	void Control();
	void MouseControl();
	void CollisionTileMap();

private:
	void CreateClips();	

private:
	AnimState curState = Move;
	Vector2 velocity;

	vector<Vector2> path;

	vector<Clip*> clips;	
	TileMap* tileMap = nullptr;	
};