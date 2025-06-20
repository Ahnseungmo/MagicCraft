#pragma once

class Option : public RectCollider {

public:

	Option();
	Option(Option* option);
	~Option();

	void Update();
	void Render();

	void SetImage(Quad* image) { this->image = image; this->image->SetParent(this); }
	void SetEvent(function<void(void*)> event) { this->spellEvent = event; }
	void RunOption(SpellOptionData* data) {if(spellEvent!=nullptr) spellEvent(data); }

private:
	Quad* image;
	function<void(void*)> spellEvent = nullptr;
};