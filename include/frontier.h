#ifndef FRONTIER_H
#define FRONTIER_H

#include <unordered_map>
#include <queue>
#include <vector>
#include "node.h"

struct FrontierNode{
    Node* node;
    Node* prevNode;
    FrontierNode* next;
    FrontierNode* prev;
    int pathCost;
    int heuristic;
};

class Frontier {
public:
    Frontier();
    void push_back(Node* node, Node* prevNode, int val=0);
    void push_front(Node* node, Node* prevNode, int val=0);
    Node* pop_back(std::unordered_map<Node*, Node*>& history);
    Node* pop_front(std::unordered_map<Node*, Node*>& history);
    Node* pop_min(std::unordered_map<Node*, Node*>& history);
    FrontierNode* getHead();
    FrontierNode* getTail();
    bool empty();
    FrontierNode* find(Node* node);
    void update(FrontierNode* fnode);

private:
    FrontierNode* head;
    FrontierNode* tail;
    int size;
    std::unordered_map<Node*, FrontierNode*> nodeMap;

    struct compare{
        bool operator()(const FrontierNode l, const FrontierNode r)
        {
           return l.heuristic + l.pathCost > r.heuristic + r.pathCost;
        }
    };
    std::priority_queue<FrontierNode, std::vector<FrontierNode>, compare> minNodeHeap;
    Node* remove(FrontierNode* fnode, std::unordered_map<Node*, Node*>& history);



};

#endif
