#include "frontier.h"

using namespace std;

Frontier::Frontier(){
    head = NULL;
    tail = NULL;
    size = 0;
}

void Frontier::push_back(Node* node, int val){
    FrontierNode* fnode = new FrontierNode;
    fnode->node = node;
    fnode->next = NULL;
    fnode->prev = tail;
    fnode->value = val;
    tail = fnode;
    nodeMap[node] = fnode;
    size++;
}

void Frontier::push_front(Node* node, int val){
    FrontierNode* fnode = new FrontierNode;
    fnode->node = node;
    fnode->next = head;
    fnode->prev = NULL;
    fnode->value = val;
    head = fnode;
    nodeMap[node] = fnode;
    size++;
}

Node* Frontier::pop_back(){
    Node* ret = tail->node;
    tail = tail->prev;
    delete tail->next;
    tail->next = NULL;
    size--;
    nodeMap.erase(ret);
    return ret;
}

Node* Frontier::pop_front(){
    Node* ret = head->node;
    head = head->next;
    delete head->prev;
    head->prev = NULL;
    size--;
    nodeMap.erase(ret);
    return ret;
}

FrontierNode* Frontier::getHead(){
    return head;
}

FrontierNode* Frontier::getTail(){
    return tail;
}

bool Frontier::empty(){
    return size == 0;
}

Node* Frontier::remove(FrontierNode* fnode){
    Node* ret = fnode->node;
    FrontierNode* prev = fnode->prev;
    FrontierNode* next = fnode->next;
    delete fnode;
    if(prev != NULL){
        prev->next = next;
    }
    if(next != NULL){
        next->prev = prev;
    }
    size --;
    nodeMap.erase(ret);
    return ret;
}

FrontierNode* Frontier::find(Node* node){
    if(nodeMap.find(node) != nodeMap.end())
        return nodeMap[node];
    else
        return NULL;
}
