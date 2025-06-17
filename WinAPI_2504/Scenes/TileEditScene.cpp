#include "Framework.h"
#include "TileEditScene.h"

TileEditScene::TileEditScene()
{
	LoadTextures();
}

TileEditScene::~TileEditScene()
{
	DeleteEditTiles();
}

void TileEditScene::Update()
{
	if (ImGui::GetIO().WantCaptureMouse) return;

	switch (editType)
	{
	case TileEditScene::BG:
		EditBGTiles();
		break;
	case TileEditScene::OBJ:
		EditObjTiles();
		break;	
	}	
}

void TileEditScene::Render()
{
	for (EditTile* tile : bgEditTiles)
	{
		tile->Render();
	}

	for (EditTile* tile : objEditTiles)
	{
		tile->Render();
	}
}

void TileEditScene::GUIRender()
{
	ImGui::Text("Map Editor");
	SaveDialog();	
	ImGui::SameLine();
	LoadDialog();

	ImGui::DragInt("Cols", &mapCols, 1, 1, 20);
	ImGui::DragInt("Rows", &mapRows, 1, 1, 20);

	const char* editTypeNames[] = { "BG", "OBJ" };

	ImGui::ListBox("Edit Type", (int*)&editType, editTypeNames, 2);

	if (ImGui::Button("Create Tiles"))
	{
		CreateEditTiles();
	}
	
	RenderSampleButtons();
}

void TileEditScene::LoadTextures()
{
	WIN32_FIND_DATA findData;

	HANDLE handle = FindFirstFile(L"Resources/Textures/Tiles/*.png", &findData);

	bool result = true;
	wstring path = L"Resources/Textures/Tiles/";

	while (result)
	{		
		Texture* texture = Texture::Add(path + findData.cFileName);
		sampleTextures.push_back(texture);

		result = FindNextFile(handle, &findData);
	}
}

void TileEditScene::RenderSampleButtons()
{
	ImGui::DragInt("Col", &sampleButtonCols);

	if (ImGui::TreeNode("Sample Buttons"))
	{
		int count = 0;

		for (Texture* texture : sampleTextures)
		{
			string key = Utility::ToString(texture->GetFile());
			ImTextureID imguiTextureID = (ImTextureID)texture->GetSRV();

			if (ImGui::ImageButton(key.c_str(), imguiTextureID, ImVec2(50, 50)))
			{
				selectTexture = texture;
			}

			count++;

			if(count % sampleButtonCols)
			{
				ImGui::SameLine();
			}
		}

		ImGui::TreePop();
	}
}

void TileEditScene::CreateEditTiles()
{
	DeleteEditTiles();

	Vector2 size = sampleTextures[0]->GetSize();
	Vector2 startPos = Vector2(size.x * 0.5f, SCREEN_HEIGHT - size.y * 0.5f);

	imageSize = size;

	for (int y = 0; y < mapRows; y++)
	{
		for (int x = 0; x < mapCols; x++)
		{
			EditTile* tile = new EditTile();
			Vector2 pos = startPos + Vector2(x * tile->Size().x, -y * tile->Size().y);
			tile->SetLocalPosition(pos);
			tile->UpdateWorld();

			bgEditTiles.push_back(tile);
		}
	}

	tileSize = bgEditTiles.front()->Size();
}

void TileEditScene::DeleteEditTiles()
{
	for (EditTile* tile : bgEditTiles)
	{
		delete tile;
	}

	bgEditTiles.clear();
}

void TileEditScene::EditBGTiles()
{
	if (Input::Get()->IsKeyPress(VK_LBUTTON) == false)
		return;

	for (EditTile* tile : bgEditTiles)
	{
		if (tile->IsPointCollision(mousePos))
		{			
			tile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);			
		}
	}
}

void TileEditScene::EditObjTiles()
{
	if (Input::Get()->IsKeyDown(VK_LBUTTON) == false)
		return;

	for (EditTile* tile : bgEditTiles)
	{
		if (tile->IsPointCollision(mousePos))
		{
			Vector2 pos = tile->GetLocalPosition();

			EditTile* objTile = new EditTile();
			objTile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
			objTile->SetLocalPosition(pos);
			objTile->UpdateWorld();

			objEditTiles.push_back(objTile);

			sort(objEditTiles.begin(), objEditTiles.end(), EditTile::IsCompare);
		}
	}
}

void TileEditScene::Save(string file)
{
	BinaryWriter* writer = new BinaryWriter(file);

	writer->Int(mapCols);
	writer->Int(mapRows);

	writer->Vector(tileSize);
	writer->Vector(imageSize);

	for (EditTile* tile : bgEditTiles)
	{
		writer->WString(tile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
	}

	writer->Int(objEditTiles.size());
	for (EditTile* tile : objEditTiles)
	{
		writer->Vector(tile->GetLocalPosition());
		writer->WString(tile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
	}

	delete writer;
}

void TileEditScene::Load(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	if (reader->IsFailed())
	{
		delete reader;
		return;
	}

	mapCols = reader->Int();
	mapRows = reader->Int();

	tileSize = reader->Vector();
	imageSize = reader->Vector();

	CreateEditTiles();

	for (EditTile* tile : bgEditTiles)
	{
		wstring file = reader->WString();
		tile->GetImage()->GetMaterial()->SetBaseMap(file);
	}

	int objTileCount = reader->Int();

	for (int i = 0; i < objTileCount; i++)
	{
		Vector2 pos = reader->Vector();
		wstring file = reader->WString();
		EditTile* objTile = new EditTile();
		objTile->GetImage()->GetMaterial()->SetBaseMap(file);
		objTile->SetLocalPosition(pos);
		objTile->UpdateWorld();

		objEditTiles.push_back(objTile);
	}

	delete reader;
}

void TileEditScene::SaveDialog()
{
	string key = "Save";

	if (ImGui::Button(key.c_str()))
	{
		DIALOG->OpenDialog(key, key, ".map");
	}

	if (DIALOG->Display(key))
	{
		if (DIALOG->IsOk())
		{
			char temp[256] = {};
			GetCurrentDirectoryA(256, temp);
			string path = temp;
			string file = DIALOG->GetFilePathName();
			file = file.substr(path.size() + 1);
			Save(file);
		}
		
		DIALOG->Close();
	}
}

void TileEditScene::LoadDialog()
{
	string key = "Load";

	if (ImGui::Button(key.c_str()))
	{
		DIALOG->OpenDialog(key, key, ".map");
	}

	if (DIALOG->Display(key))
	{
		if (DIALOG->IsOk())
		{
			char temp[256] = {};
			GetCurrentDirectoryA(256, temp);
			string path = temp;
			string file = DIALOG->GetFilePathName();
			file = file.substr(path.size() + 1);
			Load(file);
		}

		DIALOG->Close();
	}
}
