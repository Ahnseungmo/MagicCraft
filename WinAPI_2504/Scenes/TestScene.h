#pragma once

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update() override;
	void Render() override;

private:
	Spell* spell;

};