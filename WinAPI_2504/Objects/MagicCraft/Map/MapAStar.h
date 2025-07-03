#pragma once

class MapAStar
{
public:
    MapAStar(class GameMap* map);
    ~MapAStar();

    void Render();

    int FindCloseNode(const Vector2& pos);

    int FindCloseNodeIndex(const int& index);


    void GetPath(IN const int& start, IN const int& end, OUT vector<Vector2>& path);
    vector<Vector2> GetPath(const int& start, const int& end,int size = 1);

    vector<Vector2> GetPathToTarget(int start, int targetIndex, int size);

private:
    void Reset();

    float GetManhattanDistance(int start, int end);
    float GetDiagonalManhattanDistance(const int& start, const int& end);


    void Extend(const int& center, const int& end,int size = 1);
    int GetMinNode();

    void SetEdge();

    bool IsWalkableForSize(int index, int size);

    int FindNearestReachableAround(int targetIndex, int unitSize);




private:
    vector<Node*> nodes;
    //vector<int> openNodes;
    Heap* heap;

    Vector2 tileSize;
    int cols;
};