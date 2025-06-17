#pragma once

class AnimationScene : public Scene
{
public:
	AnimationScene();
	~AnimationScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	Cookie* cookie;
	//Quad* background;
};