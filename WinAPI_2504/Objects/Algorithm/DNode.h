#pragma once

class DNode : public CircleCollider
{
private:
    friend class Dijkstra;

    struct Edge
    {
        DNode* node;
        float cost;
        LineCollider* line;

        Edge(Vector2 start, Vector2 end)
        {
            line = new LineCollider(start, end);
        }
        ~Edge()
        {
            delete line;
        }
    };

public:
    DNode(Vector2 pos);
    ~DNode();

    void Render();

    void AddEdge(DNode* node);

private:
    bool isClosed = false;

    int index = 0;
    int via = -1;

    float cost = FLT_MAX;

    vector<Edge*> edges;
};