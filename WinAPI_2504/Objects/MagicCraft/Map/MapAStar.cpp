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

    //1. ���۳�� �ʱ�ȭ �ϱ�
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
        //��ΰ� �������� ���
        if (heap->Empty())
            return;

        //2. ���³�� �߿��� ȿ���� ���� ���� ��� ã��
        int curIndex = GetMinNode();

        //3. ã�� ���� ����� ����� ���� �����ϰ� ���³�忡 �߰�
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

vector<Vector2> MapAStar::GetPath(const int& start, const int& end,int size)
{
    Reset();
    vector<Vector2> path;

    //1. ���۳�� �ʱ�ȭ �ϱ�
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
        //��ΰ� �������� ���
        if (heap->Empty())
            return path;

        //2. ���³�� �߿��� ȿ���� ���� ���� ��� ã��
        int curIndex = GetMinNode();

        //3. ã�� ���� ����� ����� ���� �����ϰ� ���³�忡 �߰�
        Extend(curIndex, end, size);
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

void MapAStar::Extend(const int& center, const int& end, int size)
{
    for (Node::Edge* edge : nodes[center]->edges)
    {

        int index = edge->index;
        if (nodes[index]->state == Node::Closed)
            continue;
        if (nodes[index]->state == Node::Obstacle)
            continue;
        if (!IsWalkableForSize(index, size))
            continue; // 2x2 ������ ����� �� ������ ����


        float G = nodes[center]->g;

        // �⺻ cost
        float cost = edge->cost;

        // [�߰�] �밢�� �̵����� Ȯ��
        Vector2 from = Vector2{ (float)(center % cols), (float)(center/cols) };
        Vector2 to = Vector2{ (float)(index % cols), (float)(index / cols) };
        Vector2 diff = to - from;

        if (abs(diff.x) == 1 && abs(diff.y) == 1) // �밢�� �̵�
        {
            // ������ ����/���� ��� Ȯ��
            int adj1 = center + diff.x;           // ����
            int adj2 = center + diff.y * cols;    // ����

            if ((nodes[adj1]->state == Node::Obstacle) || (nodes[adj2]->state == Node::Obstacle))
            {
                cost += 10000.0f; // �ſ� ���� ��� �߰� (��ǻ� ���ϵ��� ����)
            }
        }

        G += cost;

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
/*
bool MapAStar::IsWalkableForSize(int index, int size)
{
    int x = index % cols;
    int y = index / cols;

    if (x + size > cols || y + size > tileSize.y)
        return false;

    // ���� ��� �� (���� ���� ����)
    const int offset = 1;

    for (int dy = 0; dy < size; ++dy)
    {
        for (int dx = 0; dx < size; ++dx)
        {
            int cx = x + dx;
            int cy = y + dy;

            // �� �ٱ��̸� ����
            if (cx < 0 || cy < 0 || cx >= cols || cy >= tileSize.y)
                return false;

            int checkIndex = cy * cols + cx;

            if (nodes[checkIndex]->state == Node::Obstacle)
            {
                // ���� ��Ҵ��� Ȯ��: ���� �浹�ϴ� ��ġ���� üũ
                if (dx >= offset || dy >= offset)
                    return false; // ������ ���� ��´ٸ� ����
            }
        }
    }

    return true;
}
*/
bool MapAStar::IsWalkableForSize(int index, int size)
{
    int x = index % cols;
    int y = index / cols;

    if (x + size > cols || y + size > tileSize.y)
        return false;

    for (int dy = 0; dy < size; ++dy)
    {
        for (int dx = 0; dx < size; ++dx)
        {
            int checkX = x + dx;
            int checkY = y + dy;
            int checkIndex = checkY * cols + checkX;

            if (nodes[checkIndex]->state == Node::Obstacle)
                return false; // ������ ������ ��� ������ ��ġ�� �˻�
        }
    }

    return true; // ������ ������ �����ϴ� ������ obstacle ������ OK
}
int MapAStar::FindNearestReachableAround(int targetIndex, int unitSize)
{

    const Vector2 targetTile = Vector2{ (float)(targetIndex % cols), (float)(targetIndex / cols) };
    const int maxSearchRange = 5; // Ÿ�� �ֺ� �� ĭ���� �˻����� (�ʿ信 ���� ����)

    queue<int> open;
    unordered_set<int> visited;

    open.push(targetIndex);
    visited.insert(targetIndex);

    while (!open.empty())
    {
        int curIndex = open.front();
        open.pop();

        if (IsWalkableForSize(curIndex, unitSize))
        {
            return curIndex; // ������ ���� ������ ��ġ �߰�
        }

        Vector2 curTile = Vector2{ (float)(curIndex % cols), (float)(curIndex / cols) };;

        // 4���� �˻�
        static const Vector2 dirs[4] = {
            Vector2(1, 0), Vector2(-1, 0),
            Vector2(0, 1), Vector2(0, -1)
        };

        for (const Vector2& dir : dirs)
        {
            Vector2 nextTile = curTile + dir;
            int x = (int)nextTile.x;
            int y = (int)nextTile.y;

            if (x < 0 || y < 0 || x >= cols || y >= tileSize.y)
                continue;

            int nextIndex = y * cols + x;

            if (visited.count(nextIndex))
                continue;

            // �ʹ� �ָ� ���� (���� ���)
            if (abs(x - (int)targetTile.x) > maxSearchRange || abs(y - (int)targetTile.y) > maxSearchRange)
                continue;

            visited.insert(nextIndex);
            open.push(nextIndex);
        }
    }

    return -1; // ��ó�� ���� ������ ��ġ ����
}

vector<Vector2> MapAStar::GetPathToTarget(int start, int targetIndex, int size)
{
    int reachableIndex = FindNearestReachableAround(targetIndex, size);

    if (reachableIndex == -1)
        return {};

    return GetPath(start, reachableIndex,size);
}