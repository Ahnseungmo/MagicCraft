#include "Framework.h"

Bird::Bird() : RectCollider(Vector2(50, 50))
{	
	CreateFrames();	
}

Bird::~Bird()
{
	for (Quad* frame : frames)
	{
		delete frame;
	}	
}

void Bird::Update()
{
	//Gravity();
	FrameUpdate();	

	UpdateWorld();
	frames[curFrame]->UpdateWorld();
}

void Bird::Render()
{	
	frames[curFrame]->Render();
	Collider::Render();
}

void Bird::FrameUpdate()
{
	frameTimer += DELTA;

	if (frameTimer >= FRAME_TIME)
	{
		frameTimer -= FRAME_TIME;

		curFrame = ++curFrame % FRAME_SIZE;
	}
}

void Bird::Gravity()
{
	if (Input::Get()->IsKeyDown(VK_SPACE))
	{
		velocity.y = JUMP_POWER;
	}

	velocity.y -= GRAVITY * DELTA;
	localPosition.y += velocity.y * DELTA;	
}

void Bird::CreateFrames()
{
	for (int i = 0; i < FRAME_SIZE; i++)
	{
		Quad* frame = new Quad(L"Resources/Textures/Bird.png", Vector2(i / 3.0f, 0.0f), Vector2((i + 1.0f) / 3.0f, 1.0f));
		frame->SetParent(this);
		frames.push_back(frame);
	}
}
