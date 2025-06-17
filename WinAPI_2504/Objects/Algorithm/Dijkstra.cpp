#include "Framework.h"

Dijkstra::~Dijkstra()
{
    for (DNode* node : nodes)
        delete node;
}

void Dijkstra::Update()
{
    if (Input::Get()->IsKeyDown('A'))
        CreateNode(mousePos);

    if (Input::Get()->IsKeyDown(VK_RBUTTON))
    {
        for (DNode* node : nodes)
        {
            if (node->IsPointCollision(mousePos))
            {
                selectNode = node;
                break;
            }
        }
    }

    if (Input::Get()->IsKeyUp(VK_RBUTTON))
    {
        if (selectNode == nullptr) return;

        for (DNode* node : nodes)
        {
            if (node == selectNode) continue;

            if (node->IsPointCollision(mousePos))
            {
                node->AddEdge(selectNode);
                selectNode->AddEdge(node);
                break;
            }
        }
    }
}

void Dijkstra::Render()
{
    for (DNode* node : nodes)
        node->Render();
}

int Dijkstra::FindCloseNode(Vector2 pos)
{
    float minDist = FLT_MAX;

    int index = -1;

    for(int i = 0 ; i < nodes.size() ; i++)
    {
        float distance = Vector2::Distance(pos, nodes[i]->GetLocalPosition());

        if (minDist > distance)
        {
            minDist = distance;
            index = i;
        }
    }

    return index;
}

void Dijkstra::SetEdgeInfo(int curIndex)
{
    if (curIndex == -1) return;

    nodes[curIndex]->isClosed = true;

    float cost = nodes[curIndex]->cost;

    for (DNode::Edge* edge : nodes[curIndex]->edges)
    {
        if (edge->node->cost > cost + edge->cost)
        {
            edge->node->cost = cost + edge->cost;
            edge->node->via = curIndex;
        }
    }
}

int Dijkstra::FindMinCostNode()
{
    float minCost = FLT_MAX;

    int index = -1;

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->isClosed) continue;

        if (minCost > nodes[i]->cost)
        {
            minCost = nodes[i]->cost;
            index = i;
        }
    }

    return index;
}

void Dijkstra::ResetNodes()
{
    for (DNode* node : nodes)
    {
        node->isClosed = false;
        node->via = -1;
        node->cost = FLT_MAX;
    }
}

vector<Vector2> Dijkstra::GetPath(int start, int end)
{
    ResetNodes();

    //1. 시작노드 초기화
    int curIndex = start;
    nodes[curIndex]->cost = 0;
    nodes[curIndex]->via = start;

    for (DNode* node : nodes)
    {
        //2. 선택된 노드의 인접 노드 초기화하고 노드 닫기
        SetEdgeInfo(curIndex);

        //3. 열려있는 노드 중에서 가장 효율이 좋은 노드 찾기
        curIndex = FindMinCostNode();
    }

    //4. BackTracking
    curIndex = end;

    vector<Vector2> path;
    while (curIndex != start)
    {
        path.push_back(nodes[curIndex]->GetLocalPosition());
        curIndex = nodes[curIndex]->via;

        if (curIndex == -1)
            break;
    }

    path.push_back(nodes[start]->GetLocalPosition());

    return path;
}

void Dijkstra::CreateNode(Vector2 pos)
{
    DNode* node = new DNode(pos);
    node->index = nodes.size();

    nodes.push_back(node);
}
