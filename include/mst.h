#ifndef MST_H
#define MST_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "node.h"
#include "dsets.h"

struct Edge{
    Node* v1, *v2;
    int length;
};

class MST {
public:
    MST(const std::vector<Node*>& goals);
    int getTotalCost();
    static int manhattanDistance(Node* n1, Node* n2);

private:
    int numGoals, totalCost;
    struct compare{
        bool operator()(const Edge* l, const Edge* r)
        {
           return l->length > r->length;
        }
    };
    std::priority_queue<Edge*, std::vector<Edge*>, compare> minEdgeHeap;
    std::unordered_set<int> curVertices;
    DisjointSets dsets;

};

#endif
