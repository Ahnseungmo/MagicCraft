#pragma once

class SpellCustomUI : public RectCollider {

public:
	SpellCustomUI();
	~SpellCustomUI();

	void Update();
	void Render();


private:
	Quad* backGround;

};