#pragma once

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update() override;
	void Render() override;

	void GUIRender() override;

private:

	RectCollider* SandBag;

	Player* player;

	SpellCustomUI* book;
};