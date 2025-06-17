#pragma once

class AStarScene : public Scene
{
public:
	AStarScene();
	~AStarScene();

	void Update() override;
	void Render() override;
};