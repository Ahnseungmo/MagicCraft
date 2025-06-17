#pragma once

class ShootingScene : public Scene
{
public:
	ShootingScene();
	~ShootingScene();
		
	void Update() override;
	void Render() override;

private:
	Plane* plane;
	Bullet* bullet;
};