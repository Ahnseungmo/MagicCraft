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