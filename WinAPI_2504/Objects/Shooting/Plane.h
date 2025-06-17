#pragma once

class Plane : public GameObject
{
private:
	const float SPEED = 100.0f;

public:
	Plane();
	~Plane();

	void Update();
	void Render();

private:
	void ControlKeyboard();
	void ControlMouse();

private:
	void MakeMesh() override;

private:
	Collider* collider;
};