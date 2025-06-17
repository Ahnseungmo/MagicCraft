#pragma once

class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	void Update() override;
	void Render() override;

private:
	vector<VertexColor> vertices;
	vector<UINT> indices;
		
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	MatrixBuffer* worldBuffer;	

	ColorBuffer* colorBuffer;

	Matrix world;
	Float4x4 matWorld;

	Vector2 pos;
};