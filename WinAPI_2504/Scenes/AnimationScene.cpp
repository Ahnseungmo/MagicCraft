#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
	cookie = new Cookie();
	cookie->SetLocalPosition(CENTER);
}

AnimationScene::~AnimationScene()
{
	delete cookie;
}

void AnimationScene::Update()
{
	cookie->Update();
}

void AnimationScene::Render()
{
	cookie->Render();
}

void AnimationScene::GUIRender()
{
	cookie->Edit();
}
