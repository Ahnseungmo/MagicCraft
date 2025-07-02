#include "Framework.h"

MapAStar::MapAStar(GameMap* map)
{
    map->MakeNodes(nodes);

    tileSize = map->GetTileCount();
    cols = tileSize.y;

    SetEdge();

    heap = new Heap();

}

MapAStar::~MapAStar()
{
    for (Node* node : nodes)
        delete node;

    delete heap;
}


void MapAStar::Render()
{
    for (Node* node : nodes)
        node->Render();
}

int MapAStar::FindCloseNode(const Vector2& pos)
{
    float minDist = FLT_MAX;

    int index = -1;

    for (int i = 0; i < nodes.size(); i++)
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
int MapAStar::FindCloseNodeIndex(const int& index)
{
    
    /*
    float minDist = FLT_MAX;

    int index = -1;

    for (int i = 0; i < nodes.size(); i++)
    {
        float distance = Vector2::Distance(pos, nodes[i]->GetLocalPosition());

        if (minDist > distance)
        {
            minDist = distance;
            index = i;
        }
    }
    */

    return index;
}

void MapAStar::GetPath(IN const int& start, IN const int& end, OUT vector<Vector2>& path)
{
    Reset();
    path.clear();

    //1. 시작노드 초기화 하기
    float G = 0;
    float H = GetManhattanDistance(start, end);

    nodes[start]->f = G + H;
    nodes[start]->g = G;
    nodes[start]->h = H;
    nodes[start]->via = start;
    nodes[start]->state = Node::Open;

    //openNodes.push_back(start);
    heap->Insert(nodes[start]);

    while (nodes[end]->state != Node::Closed)
    {
        //경로가 막혀있을 경우
        if (heap->Empty())
            return;

        //2. 오픈노드 중에서 효율이 가장 좋은 노드 찾기
        int curIndex = GetMinNode();

        //3. 찾은 노드와 연결된 노드의 정보 갱신하고 오픈노드에 추가
        Extend(curIndex, end);
        nodes[curIndex]->state = Node::Closed;
    }

    //4. Backtracking
    int curIndex = end;

    while (curIndex != start)
    {
        nodes[curIndex]->state = Node::Using;
        path.push_back(nodes[curIndex]->GetGlobalPosition());
        curIndex = nodes[curIndex]->via;
    }
}

vector<Vector2> MapAStar::GetPath(const int& start, const int& end)
{
    Reset();
    vector<Vector2> path;

    //1. 시작노드 초기화 하기
    float G = 0;
    float H = GetManhattanDistance(start, end);

    nodes[start]->f = G + H;
    nodes[start]->g = G;
    nodes[start]->h = H;
    nodes[start]->via = start;
//    nodes[start]->state = Node::Open;

    //openNodes.push_back(start);
    heap->Insert(nodes[start]);

    while (nodes[end]->state != Node::Closed)
    {
        //경로가 막혀있을 경우
        if (heap->Empty())
            return path;

        //2. 오픈노드 중에서 효율이 가장 좋은 노드 찾기
        int curIndex = GetMinNode();

        //3. 찾은 노드와 연결된 노드의 정보 갱신하고 오픈노드에 추가
        Extend(curIndex, end);
        if(nodes[curIndex]->state != Node::Obstacle)
            nodes[curIndex]->state = Node::Closed;
    }

    //4. Backtracking
    int curIndex = end;

    while (curIndex != start)
    {
        nodes[curIndex]->state = Node::Using;
        path.push_back(nodes[curIndex]->GetGlobalPosition());
        curIndex = nodes[curIndex]->via;
    }

    return path;
}

void MapAStar::Reset()
{
    for (Node* node : nodes)
    {
        if (node->state != Node::Obstacle)
            node->state = Node::None;
    }

    heap->Clear();
    //openNodes.clear();
}

float MapAStar::GetManhattanDistance(int start, int end)
{
    Vector2 startPos(nodes[start]->GetGlobalPosition());
    Vector2 endPos(nodes[end]->GetGlobalPosition());

    Vector2 direction = endPos - startPos;

    return abs(direction.x) + abs(direction.y);
}

float MapAStar::GetDiagonalManhattanDistance(const int& start, const int& end)
{
    return 0.0f;
}

void MapAStar::Extend(const int& center, const int& end)
{
    for (Node::Edge* edge : nodes[center]->edges)
    {
        int index = edge->index;

        if (nodes[index]->state == Node::Closed)
            continue;
        if (nodes[index]->state == Node::Obstacle)
            continue;

        float G = nodes[center]->g + edge->cost;
        float H = GetManhattanDistance(index, end);
        float F = G + H;

        if (nodes[index]->state == Node::Open)
        {
            if (F < nodes[index]->f)
            {
                nodes[index]->g = G;
                nodes[index]->f = F;
                nodes[index]->via = center;
            }
        }
        else if (nodes[index]->state == Node::None)
        {
            nodes[index]->g = G;
            nodes[index]->h = H;
            nodes[index]->f = F;
            nodes[index]->via = center;
            nodes[index]->state = Node::Open;

            //openNodes.push_back(index);
            heap->Insert(nodes[index]);
        }
    }
}

int MapAStar::GetMinNode()
{
    /*int openIndex = 0;
    int nodeIndex = openNodes[openIndex];
    float minF = nodes[nodeIndex]->f;

    for(int i = 0 ; i < openNodes.size() ; i++)
    {
        nodeIndex = openNodes[i];

        if (nodes[nodeIndex]->f < minF)
        {
            minF = nodes[nodeIndex]->f;
            openIndex = i;
        }
    }

    nodeIndex = openNodes[openIndex];
    openNodes.erase(openNodes.begin() + openIndex);

    return nodeIndex;*/

    return heap->DeleteRoot()->index;
}

void MapAStar::SetEdge()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (i % cols != cols - 1)
        {
            nodes[i]->AddEdge(nodes[i + 1]);
            nodes[i + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - cols)
        {
            nodes[i]->AddEdge(nodes[i + cols]);
            nodes[i + cols]->AddEdge(nodes[i]);

            int j = cols + i - 1;
            int k = cols + i + 1;
            
            if (j % cols <= (cols + i) % cols) {
                nodes[i]->AddEdge(nodes[j]);
                nodes[j]->AddEdge(nodes[i]);
            }
            if (k % cols >= (cols + i) % cols) {
                nodes[i]->AddEdge(nodes[k]);
                nodes[k]->AddEdge(nodes[i]);
            }
        }
    }
}
