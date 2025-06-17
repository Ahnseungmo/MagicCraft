#include "Framework.h"

GameObject::GameObject()
{
    mesh = new Mesh();
	material = new Material();

    worldBuffer = new MatrixBuffer();
    
}

GameObject::GameObject(wstring shaderFile)
{
    mesh = new Mesh();
    material = new Material(shaderFile);

    worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{
    delete worldBuffer;
	delete material;
    delete mesh;
}

void GameObject::Render()
{
    if (!isActive) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);        

	material->Set();

    mesh->Draw();
}

void GameObject::SetWorld()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);
}

void GameObject::SetColor(float r, float g, float b, float a)
{
	material->SetColor(r, g, b, a);
}

void GameObject::Init()
{
    MakeMesh();
        
	mesh->CreateMesh();
}
