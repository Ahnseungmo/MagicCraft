#pragma once

class Player : public Character {


public:

	Player();
	~Player();

	void Update();

	void Edit();
	Transform* GetCameraTransform() { return cameraTransform; }

	float GetMp() { return mp; }
	float GetMpMax() { return mpMax; }
	

private:
	Transform* cameraTransform ;

	float mpMax = 100;
	float mp = mpMax;

};