#pragma once

class TextBox {
public:
	enum Align {
		Center,
		Left,
		Right
	};

	TextBox();
	~TextBox();
	void Update();
	void Render();
	 
	void SetText(string text) { this->text = text;}
	string GetText() { return text; }
	void SetFont(ImFont* font) { this->font = font; }
	void SetTextColor(ImVec4 color) { this->color = color; }
	void SetAlign(Align align) { this->align = align; }

	
	void SetParent(Transform* parent) { this->parent = parent; }
	void SetLocalPosition(Vector2 pos) { localPos = pos; }
	Vector2 GetLocalPosition() { return localPos; }

private:
	Align align = Center;
	static int ID_COUNT;
	int id = 0;
	string text;
	Vector2 localPos = {0,0};
	Transform* parent = nullptr;
	ImFont* font = nullptr;
	ImVec4 color = ImVec4(0,0,0,1.0f);
};