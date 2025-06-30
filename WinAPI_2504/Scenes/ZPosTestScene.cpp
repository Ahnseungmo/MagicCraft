#include "Framework.h"
#include "ZPosTestScene.h"

ZPosTestScene::ZPosTestScene()
{
	quad1 = new Quad(L"Resources/Textures/Test.jfif");
	quad1->SetLocalPosition(CENTER);
	quad1->SetZPos(0.3);
	quad2 = new Quad(L"Resources/Textures/Test.jfif");
	quad2->SetLocalPosition(CENTER);


}

ZPosTestScene::~ZPosTestScene()
{
	delete quad1;
	delete quad2;

}

void ZPosTestScene::Update()
{
	if (Input::Get()->IsKeyDown('Q')) {
		quad2->SetZPos(0.9f);
	}
	if (Input::Get()->IsKeyDown('E')) {
		quad2->SetZPos(0.0001f);
	}

	if (Input::Get()->IsKeyDown('A')) {
		quad2->Translate(Vector2::Left() * 200);
	}
	if (Input::Get()->IsKeyDown('D')) {
		quad2->Translate(Vector2::Right() * 200);
	}


	quad1->UpdateWorld();
	quad2->UpdateWorld();
}

void ZPosTestScene::Render()
{

	quad1->Render();
	quad2->Render();
}

void ZPosTestScene::GUIRender()
{

	float z = quad2->GetZPos();
	ImGui::DragFloat("a",&z);
}
