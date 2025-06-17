#include "Framework.h"

DNode::DNode(Vector2 pos) : CircleCollider(30.0f)
{
	localPosition = pos;
	UpdateWorld();
}

DNode::~DNode()
{
	for (Edge* edge : edges)
		delete edge;
}

void DNode::Render()
{
	Collider::Render();

	for (Edge* edge : edges)
		edge->line->Render();
}

void DNode::AddEdge(DNode* node)
{
	Edge* edge = new Edge(node->GetLocalPosition(), localPosition);
	edge->node = node;
	edge->cost = Vector2::Distance(node->GetLocalPosition(), localPosition);

	edges.push_back(edge);
}
