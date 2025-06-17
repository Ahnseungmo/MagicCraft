#include "Framework.h"

Tank::Tank()
{
	CreateClips();
	clips[Move]->Play();
}

Tank::~Tank()
{
	for (Clip* clip : clips)
	{
		delete clip;
	}
}

void Tank::Update()
{
	//Control();
	//CollisionTileMap();

	//if (Input::Get()->IsKeyDown(VK_LBUTTON))
	//{
	//	//path.push_back(mousePos);
	//	path.insert(path.begin(), mousePos);
	//}

	MouseControl();

	clips[curState]->Update();

	UpdateWorld();	
}

void Tank::Render()
{
	RectCollider::Render();

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	clips[curState]->Render();
}

void Tank::Control()
{
	bool isMove = false;

	if (Input::Get()->IsKeyPress('W'))
	{
		Translate(Vector2::Up() * SPEED * DELTA);
		localRotation.z = PI * 0.5f;
		isMove = true;
	}
	else if (Input::Get()->IsKeyPress('S'))
	{
		Translate(Vector2::Down() * SPEED * DELTA);
		localRotation.z = -PI * 0.5f;
		isMove = true;
	}
	else if (Input::Get()->IsKeyPress('D'))
	{
		Translate(Vector2::Right() * SPEED * DELTA);
		localRotation.z = 0;
		isMove = true;
	}
	else if (Input::Get()->IsKeyPress('A'))
	{
		Translate(Vector2::Left() * SPEED * DELTA);
		localRotation.z = PI;
		isMove = true;
	}

	curState = isMove ? Move : Idle;
}

void Tank::MouseControl()
{
	if (path.empty())
		return;	

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

	localRotation.z = atan2(velocity.y, velocity.x);
	Translate(velocity * SPEED * DELTA);
}

void Tank::CollisionTileMap()
{
	tileMap->PushCollision(this);
}

void Tank::CreateClips()
{
	Vector2 size(Vector2(1.0f / 8.0f, 1.0f / 4.0f));
	
	vector<Frame*> frames;

	//Idle
	Vector2 startUV = Vector2(0.0f, 0.5f);
	frames.push_back(new Frame(L"Resources/Textures/tank.png",
		startUV, startUV + size));

	clips.push_back(new Clip(frames, true));
	frames.clear();

	//Move
	for (int i = 1; i < 8; i++)
	{
		startUV = Vector2(i * size.x, 0.5f);

		frames.push_back(new Frame(L"Resources/Textures/tank.png",
			startUV, startUV + size));
	}

	clips.push_back(new Clip(frames, true));
}
