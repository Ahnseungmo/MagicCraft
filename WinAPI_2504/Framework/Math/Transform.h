#pragma once

class Transform
{
public:
	Transform();
	~Transform();

	void Translate(const Vector2& velocity)
	{
		localPosition += velocity;
	}

	void UpdateWorld();

	void Edit();

	void Save();
	void Load();

	Vector2 GetRight() { return right.GetNormalized(); }
	Vector2 GetUp() { return up.GetNormalized(); }

	Vector2 GetGlobalPosition() { return globalPosition; }
	Vector2 GetGlobalScale() { return globalScale; }

	Vector2 GetLocalPosition() { return localPosition; }
	void SetLocalPosition(float x, float y) { localPosition = { x, y }; }
	void SetLocalPosition(Vector2 pos) { this->localPosition = pos; }

	Float3 GetLocalRotation() { return localRotation; }
	void SetLocalRotation(float x, float y, float z) { localRotation = { x, y, z }; }
	void SetLocalRotation(Float3 rotation) { this->localRotation = rotation; }

	Vector2 GetLocalScale() { return localScale; }
	void SetLocalScale(float x, float y) { localScale = { x, y }; }
	void SetLocalScale(Vector2 scale) { this->localScale = scale; }

	void SetPivot(float x, float y) { pivot = { x, y }; }

	Matrix GetWorld() { return world; }
	void SetParent(Transform* transform) { parent = transform; }	

	string GetTag() { return tag; }
	void SetTag(string tag) { this->tag = tag; }

protected:
	string tag;

	Vector2 localPosition;
	Float3 localRotation;
	Vector2 localScale = { 1, 1 };	
	Vector2 pivot;

	Vector2 right = { 1, 0 };
	Vector2 up = { 0, 1 };

	Matrix world;
	Float4x4 matWorld;

private:
	Matrix S, R, T;
	Matrix P, IP;

	Vector2 globalPosition;
	Vector2 globalScale = { 1, 1 };

	Transform* parent = nullptr;
};