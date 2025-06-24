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
	void SetOnClickInt(function<void(int)> event) { this->OnClickInt = event; }
	void SetIntParameter(int intParameter) { this->intParameter = intParameter; }
	void SetHover(function<void(void*)> event) { this->OnHover = event; }
private:
	bool clickCheck = false;
	int intParameter = 0;
	Quad* image;

	function<void(void*)> OnClick = nullptr;
	function<void(int)> OnClickInt = nullptr;
	function<void(void*)> OnHover = nullptr;

};