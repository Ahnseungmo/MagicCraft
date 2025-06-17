#include "Framework.h"

Quad::Quad(Vector2 size) : size(size)
{
	Init();	
}

Quad::Quad(wstring textureFile, Vector2 startUV, Vector2 endUV)
	: startUV(startUV), endUV(endUV)
{
	material->SetBaseMap(textureFile);

	size = material->GetBaseMap()->GetSize() * (endUV - startUV);

	Init();
}

Quad::~Quad()
{
}

void Quad::Render()
{
	GameObject::Render();
}

void Quad::MakeMesh()
{
	Vector2 halfSize = size * 0.5f;

	vector<Vertex>& vertices = mesh->GetVertices();

	vertices.emplace_back(-halfSize.x, +halfSize.y, startUV.x, startUV.y);
	vertices.emplace_back(+halfSize.x, +halfSize.y, endUV.x, startUV.y);
	vertices.emplace_back(-halfSize.x, -halfSize.y, startUV.x, endUV.y);
	vertices.emplace_back(+halfSize.x, -halfSize.y, endUV.x, endUV.y);

	vector<UINT>& indices = mesh->GetIndices();

	indices = { 0, 1, 2, 2, 1, 3 };
}
