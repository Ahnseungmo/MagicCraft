#pragma once

class GameObject : public Transform
{
public:
	GameObject();
	GameObject(wstring shaderFile);
	~GameObject();	

	virtual void Render();

	void SetWorld();
	
	Material* GetMaterial() { return material; }
	Mesh* GetMesh() { return mesh; }

	void SetColor(float r, float g, float b, float a = 1.0f);

	void SetActive(bool isActive) { this->isActive = isActive; }
	bool IsActive() { return isActive; }	

protected:
	void Init();

private:
	virtual void MakeMesh() = 0;

protected:
	bool isActive = true;

	Mesh* mesh;
	Material* material;

	MatrixBuffer* worldBuffer;
	
};