#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
 //   quads.resize(SIZE);
	//for (int i = 0; i < SIZE; i++)
 //   {
 //       Quad* quad = new Quad(L"Resources/Textures/bird.png", Vector2(),
 //           Vector2(1.0f/3.0f, 1.0f));
 //       float x = GameMath::Random(0, SCREEN_WIDTH);
 //       float y = GameMath::Random(0, SCREEN_HEIGHT);
 //       quad->SetLocalPosition(x, y);
 //   
 //       //x = GameMath::Random(0.1f, 1.0f);
 //       //y = GameMath::Random(0.1f, 1.0f);    
 //       //quad->SetScale(x, y);  

 //       quad->UpdateWorld();

 //   
 //       quads[i] = quad;
 //   }

	quad = new Quad(L"Resources/Textures/items.png", Vector2(),
		Vector2(1.0f/10.0f, 1.0f/10.0f));
	quad->GetMaterial()->SetShader(L"SpriteInstancing.hlsl");

	instances.resize(SIZE);

	for (InstanceData& instance : instances)
	{
		float x = GameMath::Random(0, SCREEN_WIDTH);
		float y = GameMath::Random(0, SCREEN_HEIGHT);

		Matrix world = XMMatrixTranslation(x, y, 0.0f);

		instance.world = XMMatrixTranspose(world);
		instance.maxFrame = Float2(10, 10);

		instance.curFrame = Float2(GameMath::Random(0, 8), GameMath::Random(0, 4));
	}

	instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), SIZE);

}

InstancingScene::~InstancingScene()
{
	//for (Quad* quad : quads)
	//	delete quad;

	delete quad;
	delete instanceBuffer;
}

void InstancingScene::Update()
{
}

void InstancingScene::Render()
{
	//for (Quad* quad : quads)
	//{
	//	quad->Render();
	//}

	instanceBuffer->Set(1);

	quad->GetMaterial()->Set();
	
	quad->GetMesh()->DrawInstanced(SIZE);
}
