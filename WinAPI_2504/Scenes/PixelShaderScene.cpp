#include "Framework.h"
#include "PixelShaderScene.h"

PixelShaderScene::PixelShaderScene()
{
	quad = new Quad(L"Resources/Textures/Test.jfif");
	quad->SetLocalPosition(CENTER);	
	quad->GetMaterial()->SetShader(L"Filter.hlsl");

	valueBuffer = new FloatValueBuffer();
	radialBuffer = new FloatValueBuffer();

	addColorBuffer = new ColorBuffer();

	secondMap = Texture::Add(L"Resources/Textures/Background.png");

	valueBuffer->GetValues()[2] = quad->GetSize().x;
	valueBuffer->GetValues()[3] = quad->GetSize().y;
}

PixelShaderScene::~PixelShaderScene()
{
	delete quad;
	delete valueBuffer;
	delete addColorBuffer;
	delete radialBuffer;
}

void PixelShaderScene::Update()
{
	quad->UpdateWorld();
}

void PixelShaderScene::Render()
{
	valueBuffer->SetPS(1);
	radialBuffer->SetPS(2);
	secondMap->PSSet(1);
	//addColorBuffer->SetPS(2);
	quad->Render();
}

void PixelShaderScene::GUIRender()
{
	quad->Edit();
	//ImGui::SliderFloat("Value 1", &valueBuffer->GetValues()[0], -PI, PI);
	ImGui::DragFloat("Value 1", &valueBuffer->GetValues()[0]);
	ImGui::DragFloat("Value 2", &valueBuffer->GetValues()[1]);
	ImGui::ColorEdit4("Add Color", (float*)addColorBuffer->GetColor());

	ImGui::DragFloat("Radial X", &radialBuffer->GetValues()[0]);
	ImGui::DragFloat("Radial Y", &radialBuffer->GetValues()[1]);
	ImGui::DragFloat("Radial Z", &radialBuffer->GetValues()[2]);
}
