#pragma once

class Player : public Character {


public:

	Player();
	~Player();

	void Update();

	void Edit();
	Transform* GetCameraTransform() { return cameraTransform; };

private:
	Transform* cameraTransform ;


};