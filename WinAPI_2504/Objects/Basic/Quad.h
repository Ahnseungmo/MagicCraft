#pragma once

class Quad : public GameObject
{
public:
	Quad(Vector2 size = Vector2(1, 1));
	Quad(wstring textureFile, Vector2 startUV = Vector2(), Vector2 endUV = Vector2(1, 1));
	~Quad();

	void Render();	

	Vector2 GetSize() const { return size; }

private:
	void MakeMesh() override;

private:
	Vector2 startUV;
	Vector2 endUV = { 1, 1 };

	Vector2 size;
};