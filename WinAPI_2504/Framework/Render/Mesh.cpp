#include "Framework.h"

Mesh::~Mesh()
{
	delete vertexBuffer;

	if (indexBuffer)
		delete indexBuffer;
}

void Mesh::Draw(D3D11_PRIMITIVE_TOPOLOGY type)
{
	vertexBuffer->Set(type);

	if (indexBuffer)
	{
		indexBuffer->Set();
		DC->DrawIndexed(indices.size(), 0, 0);
	}
	else
	{
		DC->Draw(vertices.size(), 0);
	}
}

void Mesh::DrawInstanced(UINT drawCount, D3D11_PRIMITIVE_TOPOLOGY type)
{
	vertexBuffer->Set(type);

	if (indexBuffer)
	{
		indexBuffer->Set();
		DC->DrawIndexedInstanced(indices.size(), drawCount, 0, 0, 0);
	}
	else
	{
		DC->DrawInstanced(vertices.size(), drawCount, 0, 0);
	}
}

void Mesh::CreateMesh()
{
	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

	if (indices.size() > 0)
	{
		indexBuffer = new IndexBuffer(indices.data(), indices.size());
	}
}

void Mesh::UpdateVertices()
{
	vertexBuffer->Update(vertices.data(), vertices.size());
}
