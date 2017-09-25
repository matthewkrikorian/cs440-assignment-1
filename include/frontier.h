#ifndef FRONTIER_H
#define FRONTIER_H

#include <unordered_map>
#include "node.h"

struct FrontierNode{
    Node* node;
    FrontierNode* next;
    FrontierNode* prev;
    int value;
};

class Frontier {
public:
    Frontier();
    void push_back(Node* node, int val=0);
    void push_front(Node* node, int val=0);
    Node* pop_back();
    Node* pop_front();
    FrontierNode* getHead();
    FrontierNode* getTail();
    Node* remove(FrontierNode* fnode);
    bool empty();
    FrontierNode* find(Node* node);

private:
    FrontierNode* head;
    FrontierNode* tail;
    int size;
    std::unordered_map<Node*, FrontierNode*> nodeMap;



};

#endif
