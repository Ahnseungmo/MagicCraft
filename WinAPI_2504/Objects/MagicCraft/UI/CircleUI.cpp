#include "Framework.h"

CircleUI::CircleUI() : CircleCollider(100)
{

}
CircleUI::CircleUI(float radius) : CircleCollider(radius)
{
}
CircleUI::~CircleUI()
{
	for (auto& image : indexImages){
		delete image;
	}
	indexImages.clear();

	indexElement.clear();
	for (auto& selectImage : selectImages) {
		delete selectImage;
	}
	selectImages.clear();
	delete backGround;
}

void CircleUI::Update()
{
	if (!isActive) return;
	if (IsPointCollision(mousePos)) {
		if (Input::Get()->IsKeyDown(VK_LBUTTON)) {
			selecting = true;
			for (auto& image : indexImages) {
				image->SetActive(true);
			}
		}

	}
	if (selecting) {

		Vector2 dir = mousePos - GetGlobalPosition();  // 중심 기준으로 마우스 방향
		float selAngle = atan2(dir.y, dir.x);
		selAngle = -selAngle + PI / 2;
		if (selAngle < 0) selAngle += 2 * PI;

		int imagesSize = indexImages.size();
		float minDiff = FLT_MAX;
		int bestIndex = 0;

		for (int i = 0; i < imagesSize; i++) {
			float angle = i * (2 * PI) / imagesSize;
			float diff = fabs(selAngle - angle);
			if (diff > PI) diff = 2 * PI - diff; // 양방향 거리 고려

			if (diff < minDiff) {
				minDiff = diff;
				bestIndex = i;
			}
		}


		if (Input::Get()->IsKeyPress(VK_LBUTTON)) {
			for (int i = 0;i < imagesSize;i++) {
				if (bestIndex == i) hoverTimer.at(i) += DELTA;
				else hoverTimer.at(i) -= DELTA;
				hoverTimer.at(i) = GameMath::Clamp(hoverTimer.at(i), 0.0f, HOVER_TIME);
				float scale = 1.0f + 1*(hoverTimer.at(i) / HOVER_TIME);
				indexImages.at(i)->SetLocalScale(Vector2(1.0f * scale,1.0f * scale));
				indexImages.at(i)->UpdateWorld();
			}

		}
		if (Input::Get()->IsKeyUp(VK_LBUTTON)) {
			select = bestIndex;
			selecting = false;
			for (int i = 0; i < imagesSize; i++) hoverTimer.at(i) = 0;
			for (auto& image : indexImages) {
				image->SetLocalScale(Vector2(1.0f, 1.0f));
				image->UpdateWorld();
				image->SetActive(false);
			}
		}

	}



	/*
	if (selecting && Input::Get()->IsKeyPress(VK_LBUTTON)) {
		


	}


	if (selecting && Input::Get()->IsKeyUp(VK_LBUTTON)) {
		Vector2 dir = mousePos - GetGlobalPosition();  // 중심 기준으로 마우스 방향
		float selAngle = atan2(dir.y, dir.x);
		selAngle = -selAngle + PI / 2;
		if (selAngle < 0) selAngle += 2 * PI;

		int imagesSize = indexImages.size();
		float minDiff = FLT_MAX;
		int bestIndex = 0;

		for (int i = 0; i < imagesSize; i++) {
			float angle = i * (2 * PI) / imagesSize;
			float diff = fabs(selAngle - angle);
			if (diff > PI) diff = 2 * PI - diff; // 양방향 거리 고려

			if (diff < minDiff) {
				minDiff = diff;
				bestIndex = i;
			}
		}

		select = bestIndex;
		selecting = false;
		for (auto& image : indexImages) {
			image->SetActive(false);
		}
	}
	*/

	UpdateWorld();
	backGround->UpdateWorld();
	for (auto& selectImage : selectImages) {
		selectImage->UpdateWorld();
	}

	for (auto& indexImage : indexImages) {
		indexImage->UpdateWorld();
	}
//	back = indexImages.at(select);
}

void CircleUI::Render()
{
	if (!isActive) return;
	if (backGround != nullptr) {
		backGround->Render();
	}

	selectImages.at(select)->Render();
	for (auto& indexImage : indexImages) {
		indexImage->Render();
	}
	CircleCollider::Render();
}

void CircleUI::InsertIndex(Quad* quad,int element) {
	indexImages.push_back(quad);
	indexImages.back()->SetParent(this);
	indexImages.back()->SetActive(false);
	indexImages.back()->UpdateWorld();
	indexElement.push_back(element);
	hoverTimer.push_back(0.0f);

	selectImages.push_back(new Quad(quad->GetMaterial()->GetBaseMap()->GetFile()));
	selectImages.back()->SetLocalScale({ 2.0f,2.0f });
	selectImages.back()->SetParent(this);
	selectImages.back()->UpdateWorld();
}


void CircleUI::ImageRePosition() {
	int imagesSize = indexImages.size();
	for (int i = 0;i < imagesSize;i++) {
		float angle = i * (2 * PI) / imagesSize;
		Vector2 direction = (Vector2::Up())*this->Radius();
		Vector2 movePos;
		movePos.x = (direction.x * cos(angle)) + (direction.y * sin(angle));
		movePos.y = (direction.y * cos(angle)) + (direction.x * -sin(angle));

		indexImages.at(i)->SetLocalPosition(movePos);

	}
}
void CircleUI::SetBackGround(Quad* quad) {
	backGround = quad;
	backGround->SetParent(this);
	backGround->UpdateWorld();
}
