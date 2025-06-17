#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{	
	quad = new Quad(L"Resources/Textures/Background.png", Vector2(), Vector2(4, 1));
	quad->SetLocalPosition(CENTER);
	quad->UpdateWorld();		

	Vector2 size = quad->GetSize();

	bird = new Bird();
	bird->SetLocalPosition(CENTER);

	ui = new Quad(L"Resources/Textures/hp_bar.png");
	ui->SetLocalPosition(CENTER_X, SCREEN_HEIGHT * 0.9f);
	ui->UpdateWorld();

	valueBuffer = new FloatValueBuffer();	

	//renderTarget = new RenderTarget(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	renderTarget = new RenderTarget();
	Texture* textrue = Texture::Add(L"RenderTarget", renderTarget->GetSRV());

	Quad* quad = new Quad(CENTER);
	quad->GetMaterial()->SetBaseMap(textrue);
	quad->SetLocalPosition(CENTER_X * 0.5f, CENTER_Y * 0.5f);
	quad->UpdateWorld();
	quad->GetMaterial()->SetShader(L"Filter.hlsl");
	quads.push_back(quad);	

	quad = new Quad(CENTER);
	quad->GetMaterial()->SetBaseMap(textrue);
	quad->SetLocalPosition(CENTER_X * 1.5f, CENTER_Y * 1.5f);
	quad->UpdateWorld();
	quad->GetMaterial()->SetShader(L"Filter.hlsl");
	quads.push_back(quad);
}

TextureScene::~TextureScene()
{
	delete quad;	
	delete bird;

	delete ui;

	delete renderTarget;
	for (Quad* quad : quads)
		delete quad;
}

void TextureScene::Update()
{
	quad->Translate(Vector2::Left() * BG_SPEED * DELTA);
	
	if (quad->GetLocalPosition().x <= 0)
	{
		quad->Translate(Vector2::Right() * quad->GetSize().x * 0.5f);
	}

	bird->SetLocalPosition(mousePos);

	quad->UpdateWorld();
	bird->Update();
}

void TextureScene::PreRender()
{
	renderTarget->Set();

	quad->Render();
	bird->Render();	
}

void TextureScene::Render()
{
	quad->Render();
	bird->Render();

	//for (Quad* quad : quads)
	//	quad->Render();
}

void TextureScene::PostRender()
{
	valueBuffer->GetValues()[0] = 3.0f;
	valueBuffer->SetPS(1);
	quads[0]->Render();

	valueBuffer->GetValues()[0] = 1.0f;
	valueBuffer->SetPS(1);
	quads[1]->Render();

	ui->Render();
}

void TextureScene::GUIRender()
{
	ImGui::DragFloat("Value 1", &valueBuffer->GetValues()[0]);
}
