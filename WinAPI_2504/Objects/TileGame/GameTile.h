#pragma once

class GameTile : public RectCollider
{
public:
	GameTile(wstring textureFile, Vector2 size);
	~GameTile();
	
	void Render();

	void UpdateWorld();
	

private:
	Quad* image;
};