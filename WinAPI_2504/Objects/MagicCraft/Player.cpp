#include "Framework.h"

Player::Player() : CircleCollider(10)
{
	string path = "Resources/Textures/MagicCraft/Character/Player/";
	LoadClip(path, "Move_Up.xml", true, 1.0f);
	LoadClip(path, "Move_Right.xml", true, 1.0f);
	LoadClip(path, "Move_Down.xml", true, 1.0f);
	LoadClip(path, "Move_Left.xml", true, 1.0f);

}

Player::~Player()
{
	for (auto& clip : clips) {
		delete clip;
	}
	clips.clear();
}

void Player::Update()
{
	isMove = false;
	direction = Vector2(0, 0);
	if (Input::Get()->IsKeyPress('W')) {
		isMove = true;
		direction += Vector2::Up();
	}
	if (Input::Get()->IsKeyPress('S')) {
		isMove = true;
		direction += Vector2::Down();
	}
	if (Input::Get()->IsKeyPress('D')) {
		isMove = true;
		direction += Vector2::Right();
	}
	if (Input::Get()->IsKeyPress('A')) {
		isMove = true;
		direction += Vector2::Left();
	}


	Vector2 focusDirection = mousePos - GetGlobalPosition();
	float angle = atan2(focusDirection.y, focusDirection.x);


	// 라디안 기준 방향 구분 (각 범위는 45도(π/4) 기준)
	if (angle >= -PI/4 && angle < PI/4) {
		dir = Right;
	}
	else if (angle >= PI/4 && angle < 3 * PI/4) {
		dir = Up;
	}
	else if (angle >= -3 * PI/4 && angle < -PI/4) {
		dir = Down;
	}
	else {
		dir = Left;
	}



	Translate(direction * speed * DELTA);
	UpdateWorld();
	clips.at((int)dir)->Update();	

}

void Player::Render()
{
	CircleCollider::Render();
	clips.at((int)dir)->Render();

}

void Player::LoadClip(string path, string file, bool isLoop, float speed)
{
	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	document->LoadFile((path + file).c_str());

	tinyxml2::XMLElement* atlas = document->FirstChildElement();
	string textureFile = path + atlas->Attribute("imagePath");

	vector<Frame*> frames;
	tinyxml2::XMLElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;
		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		wstring file = Utility::ToWString(textureFile);
		frames.push_back(new Frame(file, x, y, w, h));

		sprite = sprite->NextSiblingElement();
	}

	clips.push_back(new Clip(frames, isLoop, speed));

	delete document;
}

void Player::Edit()
{

	Vector2 focusDirection = mousePos - GetGlobalPosition();
	float angle = atan2(focusDirection.y, focusDirection.x);
	ImGui::DragFloat("Angle", &angle);
	int a = (int)dir;
	ImGui::DragInt("Dir", &a);

}
