#pragma once

class TileEditScene : public Scene
{
private:
	enum EditType
	{
		BG = 0,
		OBJ = 1
	};

public:
	TileEditScene();
	~TileEditScene();	

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	void LoadTextures();

	void RenderSampleButtons();
	void CreateEditTiles();
	void DeleteEditTiles();	

	void EditBGTiles();
	void EditObjTiles();

	void Save(string file);
	void Load(string file);

	void SaveDialog();
	void LoadDialog();

private:
	int sampleButtonCols = 5;
	int mapCols = 5;
	int mapRows = 5;
	Vector2 tileSize;
	Vector2 imageSize;

	EditType editType = BG;

	vector<Texture*> sampleTextures;
	vector<EditTile*> bgEditTiles;
	vector<EditTile*> objEditTiles;

	Texture* selectTexture;
};