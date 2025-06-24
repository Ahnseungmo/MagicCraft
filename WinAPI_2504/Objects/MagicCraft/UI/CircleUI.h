#pragma once

class CircleUI : public CircleCollider {


public:

	CircleUI();
	CircleUI(float radius);
	~CircleUI();

	void Update();
	void Render();

	void InsertIndex(Quad* quad, int element);

	void ImageRePosition();
	void SetBackGround(Quad* quad);
	int GetSelect() { return select; }
	int GetSelectElement() { return indexElement.at(select); }
	int GetIndexElement(int i) { return indexElement.at(i); }
	void SetSelect(int select) { this->select = select; }

private:
	const float HOVER_TIME = 0.1;

	int select = 0;
	bool selecting = false;

	Quad* backGround;
	vector<Quad*> selectImages;
	vector<Quad*> indexImages;
	vector<int> indexElement;

	vector<float> hoverTimer;

};