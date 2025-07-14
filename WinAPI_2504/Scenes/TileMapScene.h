#pragma once

class TileMapScene : public Scene
{
public:
	TileMapScene();
	~TileMapScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void SetGameMapBiome();

private:
	GameMap* gameMap;
	MapAStar* aStar;

	Player* player;

//	SpellCustomUI* book;
};