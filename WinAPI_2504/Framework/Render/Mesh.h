#pragma once

class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	void Draw(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void DrawInstanced(UINT drawCount, D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void CreateMesh();

	void UpdateVertices();

	vector<Vertex>& GetVertices() { return vertices; }
	vector<UINT>& GetIndices() { return indices; }

	VertexBuffer* GetVertexBuffer() { return vertexBuffer; }
	IndexBuffer* GetIndexBuffer() { return indexBuffer; }

private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;

	vector<Vertex> vertices;
	vector<UINT> indices;
};