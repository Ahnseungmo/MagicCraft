#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
	plane = new Plane();
	//plane->SetPivot(0, +50);

	bullet = new Bullet();
}

ShootingScene::~ShootingScene()
{
	delete plane;
	delete bullet;
}

void ShootingScene::Update()
{
	plane->Update();
	bullet->Update();
}

void ShootingScene::Render()
{
	plane->Render();
	bullet->Render();
}
