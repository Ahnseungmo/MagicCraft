#pragma once

class Button : public RectCollider {

public:
	Button();
	Button(wstring path);
	~Button();
	void SetImage(wstring path);
	void Update();
	void Render();
	void SetOnClick(function<void(void*)> event) { this->OnClick = event; }
	void SetHover(function<void(void*)> event) { this->OnHover = event; }
private:
	Quad* image;
	function<void(void*)> OnClick = nullptr;
	function<void(void*)> OnHover = nullptr;

};