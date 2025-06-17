#pragma once

class PixelShaderScene : public Scene
{
public:
	PixelShaderScene();
	~PixelShaderScene();	

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	Quad* quad;
	FloatValueBuffer* valueBuffer;
	FloatValueBuffer* radialBuffer;
	ColorBuffer* addColorBuffer;

	Texture* secondMap;
};
