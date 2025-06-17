#pragma once

class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	vector<Collider*> colliders;

	Vector2 overlap;
};