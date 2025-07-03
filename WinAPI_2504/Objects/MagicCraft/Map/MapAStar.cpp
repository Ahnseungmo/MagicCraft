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

vector<Vector2> MapAStar::GetPath(const int& start, const int& end,int size)
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
            continue; // 2x2 몸집이 통과할 수 없으면 무시


        float G = nodes[center]->g;

        // 기본 cost
        float cost = edge->cost;

        // [추가] 대각선 이동인지 확인
        Vector2 from = Vector2{ (float)(center % cols), (float)(center/cols) };
        Vector2 to = Vector2{ (float)(index % cols), (float)(index / cols) };
        Vector2 diff = to - from;

        if (abs(diff.x) == 1 && abs(diff.y) == 1) // 대각선 이동
        {
            // 사이의 가로/세로 노드 확인
            int adj1 = center + diff.x;           // 수평
            int adj2 = center + diff.y * cols;    // 수직

            if ((nodes[adj1]->state == Node::Obstacle) || (nodes[adj2]->state == Node::Obstacle))
            {
                cost += 10000.0f; // 매우 높은 비용 추가 (사실상 피하도록 유도)
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

    // 예외 허용 폭 (벽에 근접 가능)
    const int offset = 1;

    for (int dy = 0; dy < size; ++dy)
    {
        for (int dx = 0; dx < size; ++dx)
        {
            int cx = x + dx;
            int cy = y + dy;

            // 맵 바깥이면 막힘
            if (cx < 0 || cy < 0 || cx >= cols || cy >= tileSize.y)
                return false;

            int checkIndex = cy * cols + cx;

            if (nodes[checkIndex]->state == Node::Obstacle)
            {
                // 벽에 닿았는지 확인: 실제 충돌하는 위치인지 체크
                if (dx >= offset || dy >= offset)
                    return false; // 완전히 벽에 닿는다면 못감
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
                return false; // 보스가 실제로 밟고 지나갈 위치만 검사
        }
    }

    return true; // 보스가 실제로 점유하는 범위만 obstacle 없으면 OK
}
int MapAStar::FindNearestReachableAround(int targetIndex, int unitSize)
{

    const Vector2 targetTile = Vector2{ (float)(targetIndex % cols), (float)(targetIndex / cols) };
    const int maxSearchRange = 5; // 타깃 주변 몇 칸까지 검사할지 (필요에 따라 증가)

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
            return curIndex; // 보스가 접근 가능한 위치 발견
        }

        Vector2 curTile = Vector2{ (float)(curIndex % cols), (float)(curIndex / cols) };;

        // 4방향 검사
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

            // 너무 멀면 무시 (성능 고려)
            if (abs(x - (int)targetTile.x) > maxSearchRange || abs(y - (int)targetTile.y) > maxSearchRange)
                continue;

            visited.insert(nextIndex);
            open.push(nextIndex);
        }
    }

    return -1; // 근처에 도달 가능한 위치 없음
}

vector<Vector2> MapAStar::GetPathToTarget(int start, int targetIndex, int size)
{
    int reachableIndex = FindNearestReachableAround(targetIndex, size);

    if (reachableIndex == -1)
        return {};

    return GetPath(start, reachableIndex,size);
}