#include "frontier.h"

using namespace std;

Frontier::Frontier(){
    head = NULL;
    tail = NULL;
    size = 0;
}

void Frontier::push_back(Node* node, Node* prevNode, int val){
    FrontierNode* fnode = new FrontierNode;
    fnode->node = node;
    fnode->prevNode = prevNode;
    fnode->next = NULL;
    fnode->prev = tail;
    fnode->value = val;
    tail = fnode;
    if(tail->prev != NULL){
        tail->prev->next = tail;
    }
    if(head == NULL){
        head = tail;
    }
    nodeMap[node] = fnode;
    size++;
}

void Frontier::push_front(Node* node, Node* prevNode, int val){
    FrontierNode* fnode = new FrontierNode;
    fnode->node = node;
    fnode->prevNode = prevNode;
    fnode->next = head;
    fnode->prev = NULL;
    fnode->value = val;
    head = fnode;
    if(head->next != NULL){
        head->next->prev = head;
    }
    if(tail == NULL){
        tail = head;
    }
    nodeMap[node] = fnode;
    size++;
}

Node* Frontier::pop_back(unordered_map<Node*, Node*>& history){
    Node* ret = tail->node;
    Node* prevNode = tail->prevNode;
    FrontierNode* prev = tail->prev;
    delete tail;
    if(prev != NULL)
        prev->next = NULL;
    if(head == tail){
        head = NULL;
    }
    tail = prev;
    size--;
    nodeMap.erase(ret);
    history[ret] = prevNode;
    return ret;
}

Node* Frontier::pop_front(unordered_map<Node*, Node*>& history){
    Node* ret = head->node;
    Node* prevNode = head->prevNode;
    FrontierNode* next = head->next;
    delete head;
    if(next != NULL)
        next->prev = NULL;
    if(head == tail){
        tail = NULL;
    }
    head = next;
    size--;
    nodeMap.erase(ret);
    history[ret] = prevNode;
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
    if(head == fnode){
        head = next;
    }
    if(tail == fnode){
        tail = prev;
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
