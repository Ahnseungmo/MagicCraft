#include "Framework.h"
#include "ValueBar.h"

ValueBar::ValueBar(wstring str) : Quad(str, Vector2(), Vector2(1, 1))
{
	
	GetMaterial()->SetShader(L"ProgressBar.hlsl");
	valueBuffer = new FloatValueBuffer();
}

ValueBar::~ValueBar()
{
	delete valueBuffer;
}

void ValueBar::Render() {
	valueBuffer->GetValues()[0] = data;
	valueBuffer->SetPS(1);
	Quad::Render();
}