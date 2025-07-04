#pragma once

class Node : public Transform
{
public:
    friend class AStar;

    enum State
    {
        None, Open, Closed, Using, Obstacle
    };

    struct Edge
    {
        int index;
        float cost;
        Vector2 start, end;
  
        Edge(Vector2 start, Vector2 end) : start(start),end(end)
        {

        }
        ~Edge()
        {
 
        }
    };

private:

public:
    Node(Vector2 pos, int index);
    ~Node();

    void Render();

    void AddEdge(Node* node);

    void SetState(State state) { this->state = state; }
    float GetCost() { return f; }
    float f = 0, g = 0, h = 0;
    State state = None;

    int index = 0;
    int via = -1;

    //G : 시작점 부터 노드까지의 가중치
    //H : 노드부터 목적지까지의 추정 가중치
    //F : G + H
    //Cost


    vector<Edge*> edges;
private:

};