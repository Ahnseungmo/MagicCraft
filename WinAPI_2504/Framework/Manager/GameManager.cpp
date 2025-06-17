#include "Framework.h"

//#include "Scenes/TutorialScene.h"
#include "Scenes/ShootingScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/TextureScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/PixelShaderScene.h"
#include "Scenes/TileEditScene.h"
#include "Scenes/TileGameScene.h"
#include "Scenes/DijkstraScene.h"
#include "Scenes/AStarScene.h"
#include "Scenes/InstancingScene.h"
#include "Scenes/InstancingMapEditorScene.h"
#include "Scenes/TestScene.h"

GameManager::GameManager()
{
	Create();
		
	//SCENE->AddScene("Game", new TutorialScene());	
	//SCENE->AddScene("Game", new ShootingScene());
	//SCENE->AddScene("Game", new CollisionScene());
	//SCENE->AddScene("Game", new TextureScene());
	//SCENE->AddScene("Game", new AnimationScene());
	//SCENE->AddScene("Game", new PixelShaderScene());
	//SCENE->AddScene("Game", new TileEditScene());
	//SCENE->AddScene("Game", new TileGameScene());
	//SCENE->AddScene("Game", new DijkstraScene());
	//SCENE->AddScene("Game", new AStarScene());
	//SCENE->AddScene("Game", new InstancingScene());
	//SCENE->AddScene("Game", new InstancingMapEditorScene());
	SCENE->AddScene("Game", new TestScene());

	SCENE->ChangeScene("Game");
}

GameManager::~GameManager()
{
	Release();
}

void GameManager::Update()
{
	Timer::Get()->Update();
	Input::Get()->Update();
	Audio::Get()->Update();

	Environment::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
	SCENE->PreRender();
	
	Environment::Get()->SetViewport();
	Device::Get()->Clear();	

	SCENE->Render();

	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	SCENE->GUIRender();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();
	Audio::Get();

	Device::Get();

	SceneManager::Get();

	Environment::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

	Device::Delete();
	Shader::Delete();
	Texture::Delete();
	Audio::Delete();

	SceneManager::Delete();

	Environment::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
