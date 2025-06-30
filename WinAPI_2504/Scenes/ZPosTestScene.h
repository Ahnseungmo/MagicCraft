#pragma once

class ZPosTestScene : public Scene
{
public:
	ZPosTestScene();
	~ZPosTestScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	Quad* quad1;
	Quad* quad2;

};
