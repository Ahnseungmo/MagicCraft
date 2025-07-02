#pragma once

class TileMapScene : public Scene
{
public:
	TileMapScene();
	~TileMapScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	GameMap* gameMap;
	MapAStar* aStar;

	Player* player;
};