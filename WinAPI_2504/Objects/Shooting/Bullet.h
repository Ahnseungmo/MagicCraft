#pragma once

class Bullet : public GameObject
{
private:
	const float SPEED = 5.0f;

public:
	Bullet();
	~Bullet();

	void Update();

private:
	void MakeMesh() override;

private:
	Vector2 direction = { 0, 1 };	
};