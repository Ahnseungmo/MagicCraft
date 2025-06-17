#pragma once

class Bird : public RectCollider
{
private:
	const UINT FRAME_SIZE = 3;
	const float FRAME_TIME = 0.1f; // 100ms per frame
	const float GRAVITY = 980.0f; // Gravity force applied to the bird
	const float JUMP_POWER = 500.0f;

public:
	Bird();
	~Bird();

	void Update();
	void Render();
	
private:
	void FrameUpdate();
	void Gravity();
	void CreateFrames();

private:	
	UINT curFrame = 1;
	float frameTimer = 0.0f;

	vector<Quad*> frames;

	Vector2 velocity;
};