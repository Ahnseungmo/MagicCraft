#include "Framework.h"
#include "InstancingMapEditorScene.h"

InstancingMapEditorScene::InstancingMapEditorScene()
{
	sampleTilemap = new Quad(L"Resources/Textures/tilemap.png");
	sampleTilemap->SetTag("SampleTilemap");
	sampleTilemap->Load();

	tileQuad = new Quad(L"Resources/Textures/tilemap.png", Vector2(),
		Vector2(1.0f / 18.0f, 0.1f));
	tileQuad->GetMaterial()->SetShader(L"SpriteInstancing.hlsl");
	tileQuad->SetTag("TileQuad");
	tileQuad->Load();

	CreateTiles();	

	Audio::Get()->Add("BGM", "Resources/Sounds/wave.mp3", true);
	Audio::Get()->Add("Click", "Resources/Sounds/Click2.wav");
	Audio::Get()->Add("Click2", "Resources/Sounds/swish.wav");
	Audio::Get()->Add("Click3", "Resources/Sounds/Click.wav");

	Audio::Get()->Play("BGM", 0.5f);
}

InstancingMapEditorScene::~InstancingMapEditorScene()
{
	delete sampleTilemap;

	delete tileQuad;
	delete instanceBuffer;
}

void InstancingMapEditorScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_RBUTTON))
	{
		Audio::Get()->Play("Click3");
	}

	SetTileCoord();
	SelectSampleTile();
	EditTile();

	tileQuad->UpdateWorld();
	sampleTilemap->UpdateWorld();
}

void InstancingMapEditorScene::Render()
{
	sampleTilemap->Render();

	instanceBuffer->Set(1);

	tileQuad->SetWorld();
	tileQuad->GetMaterial()->Set();	

	tileQuad->GetMesh()->DrawInstanced(width * height);
}

void InstancingMapEditorScene::GUIRender()
{
	sampleTilemap->Edit();
	tileQuad->Edit();

	ImGui::Text("Sample Tile Coord: (%d, %d)", samleTileCoord.x, samleTileCoord.y);
	ImGui::Text("Edit Tile Coord: (%d, %d)", editTileCoord.x, editTileCoord.y);
	ImGui::Text("Selected Tile Coord: (%d, %d)", selectedTileCoord.x, selectedTileCoord.y);
}

void InstancingMapEditorScene::SetTileCoord()
{
	Vector2 halfSize = sampleTilemap->GetSize() * 0.5f * sampleTilemap->GetLocalScale();
	Vector2 leftTop = sampleTilemap->GetLocalPosition() - halfSize;

	Vector2 tileSize = sampleTilemap->GetSize() * sampleTilemap->GetLocalScale() / Vector2(18.0f, 11.0f);

	Vector2 pos = mousePos - leftTop;

	Vector2 tempCoord = pos / tileSize;
	samleTileCoord = { (int)tempCoord.x, 10 - (int)tempCoord.y };

	Vector2 leftBottom = tileQuad->GetLocalPosition();

	pos = mousePos - leftBottom;

	tempCoord = pos / tileQuad->GetSize();
	editTileCoord = { (int)tempCoord.x, (int)tempCoord.y };
}

void InstancingMapEditorScene::CreateTiles()
{
	instances.resize(width * height);

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			UINT index = y * width + x;

			float posX = x * tileQuad->GetSize().x + tileQuad->GetSize().x * 0.5f;
			float posY = y * tileQuad->GetSize().y + tileQuad->GetSize().y * 0.5f;

			Matrix world = XMMatrixTranslation(posX, posY, 0.0f);
			instances[index].world = XMMatrixTranspose(world);
			instances[index].maxFrame = Float2(18, 11);
			instances[index].curFrame = Float2(5, 0);
		}
	}

	instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), instances.size());
}

void InstancingMapEditorScene::SelectSampleTile()
{
	if (Input::Get()->IsKeyDown(VK_LBUTTON))
	{	

		if (samleTileCoord.x < 0 || samleTileCoord.x >= 18 ||
			samleTileCoord.y < 0 || samleTileCoord.y >= 10)
			return;

		Audio::Get()->Play("Click");

		selectedTileCoord = samleTileCoord;
	}
}

void InstancingMapEditorScene::EditTile()
{
	if (editTileCoord.x < 0 || editTileCoord.x >= width ||
		editTileCoord.y < 0 || editTileCoord.y >= height)
		return;

	if (Input::Get()->IsKeyDown(VK_LBUTTON))
		Audio::Get()->Play("Click2");

	if (!Input::Get()->IsKeyPress(VK_LBUTTON)) return;	

	UINT index = editTileCoord.y * width + editTileCoord.x;

	instances[index].curFrame = Float2(selectedTileCoord.x, selectedTileCoord.y);

	instanceBuffer->Update(instances.data(), instances.size());
}
