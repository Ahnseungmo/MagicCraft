#pragma once

class EditTile : public RectCollider
{
public:
	EditTile();
	~EditTile();

	void UpdateWorld();
	void Render();
	
	Quad* GetImage() { return image; }

	static bool IsCompare(EditTile* a, EditTile* b)
	{
		return a->GetLocalPosition().y > b->GetLocalPosition().y;
	}
private:
	Quad* image;
};