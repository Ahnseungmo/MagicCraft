#include "framework.h"

GameMap::GameMap()
{

	quad = new Quad(L"Resources/Textures/MagicCraft/TileMap/BiomeTiles.png", Vector2(),
		Vector2(1.0f / 30.0f, 1.0f / 16.0f));
	quad->GetMaterial()->SetShader(L"SpriteInstancing.hlsl");


	tiles.reserve(tileCount.x * tileCount.y);
	float mapLeft = -tileSize.x * (tileCount.x/2);
	float mapTop = -tileSize.y * (tileCount.y/2);
	for (int y = 0;y < tileCount.y;y++) {
		for (int x = 0;x < tileCount.x;x++) {
			tiles.push_back(new Tile(tileSize));
			tiles.back()->SetParent(this);
			tiles.back()->SetLocalPosition(mapLeft + tileSize.x * x,mapTop + tileSize.y * y);
			tiles.back()->UpdateWorld();
		}
	}

	instances.resize(size);
	for (auto& tile : tiles) {

	}


	for (InstanceData& instance : instances)
	{

		float x = GameMath::Random(0, SCREEN_WIDTH);
		float y = GameMath::Random(0, SCREEN_HEIGHT);

		Matrix world = XMMatrixTranslation(x, y, 0.0f);

		instance.world = XMMatrixTranspose(world);
		instance.maxFrame = Float2(30, 16);

		instance.curFrame = Float2(GameMath::Random(0, 8), GameMath::Random(0, 4));
	}

	instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), size);

}

GameMap::~GameMap()
{
	delete quad;
}

void GameMap::Update()
{
}

void GameMap::Render()
{

	instanceBuffer->Set(1);

	quad->GetMaterial()->Set();

	quad->GetMesh()->DrawInstanced(size);
}
