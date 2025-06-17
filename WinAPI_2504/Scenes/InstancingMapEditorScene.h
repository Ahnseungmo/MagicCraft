#pragma once

class InstancingMapEditorScene : public Scene
{
private:
	const UINT MAX_WIDTH = 30;
	const UINT MAX_HEIGHT = 30;

public:
	InstancingMapEditorScene();
	~InstancingMapEditorScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	void SetTileCoord();	
	void CreateTiles();	
	void SelectSampleTile();
	void EditTile();

private:
	Quad* sampleTilemap;

	POINT samleTileCoord;	
	POINT editTileCoord;
	POINT selectedTileCoord;

	Quad* tileQuad;

	vector<InstanceData> instances;
	VertexBuffer* instanceBuffer;

	UINT width = MAX_WIDTH, height = MAX_HEIGHT;
};