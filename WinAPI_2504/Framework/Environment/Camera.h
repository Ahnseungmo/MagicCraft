#pragma once

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();

	void SetTarget(Transform* target) { this->target = target; }
private:
	void FreeMode();
	void FollowMode();

private:
	float speed = 300.0f;
	Matrix view;

	MatrixBuffer* viewBuffer;	

	Transform* target;
};