#include "frontier.h"

using namespace std;

Frontier::Frontier(){
    head = NULL;
    tail = NULL;
    size = 0;
}

Frontier::~Frontier(){
    unordered_map<Node*, Node*> fakeHistory;
    while(!empty()){
        FrontierNode* cur = remove(getHead(), fakeHistory);
        delete cur;
    }
}

void Frontier::push_back(Node* node, Node* prevNode, int hval, int cost){
    FrontierNode* fnode = new FrontierNode;
    fnode->node = node;
    fnode->prevNode = prevNode;
    fnode->next = NULL;
    fnode->prev = tail;
    fnode->heuristic = hval;
    fnode->pathCost = cost;
    minNodeHeap.push(*fnode);
    if(head == NULL){
        head = fnode;
    }
    tail = fnode;
    if(tail->prev != NULL){
        tail->prev->next = tail;
    }
    nodeMap[node] = fnode;
    size++;
}

void Frontier::push_front(Node* node, Node* prevNode, int hval, int cost){
    FrontierNode* fnode = new FrontierNode;
    fnode->node = node;
    fnode->prevNode = prevNode;
    fnode->next = head;
    fnode->prev = NULL;
    fnode->heuristic = hval;
    fnode->pathCost = cost;
    minNodeHeap.push(*fnode);
    if(tail == NULL){
        tail = fnode;
    }
    head = fnode;
    if(head->next != NULL){
        head->next->prev = head;
    }
    nodeMap[node] = fnode;
    size++;
}

FrontierNode* Frontier::pop_back(unordered_map<Node*, Node*>& history){
    if(empty()) return NULL;
    return remove(tail, history);
}

FrontierNode* Frontier::pop_front(unordered_map<Node*, Node*>& history){
    if(empty()) return NULL;
    return remove(head, history);
}

FrontierNode* Frontier::pop_min(unordered_map<Node*, Node*>& history){
    FrontierNode* actual;
    while(!minNodeHeap.empty()){
        FrontierNode cur = minNodeHeap.top();
        minNodeHeap.pop();
        actual = this->find(cur.node);
        if(actual == NULL) continue;
        //Make sure that FrontierNode in minNodeHeap was up to date
        if(cur.pathCost != actual->pathCost || cur.heuristic != actual->heuristic){
            continue;
        }
        else {
            //If it was up to date, remove it and return it
            return remove(actual, history);
        }
    }
    return NULL;
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

int Frontier::getSize(){
    return size;
}

FrontierNode* Frontier::remove(FrontierNode* fnode, unordered_map<Node*, Node*>& history){
    Node* ret = fnode->node;
    Node* prevNode = fnode->prevNode;
    FrontierNode* prev = fnode->prev;
    FrontierNode* next = fnode->next;
    if(prev != NULL){
        prev->next = next;
    }
    if(next != NULL){
        next->prev = prev;
    }
    if(head == tail){
        //do nothing
        head = NULL;
        tail = head;
    }
    else if(head == fnode){
        head = next;
    }
    else if(tail == fnode){
        tail = prev;
    }
    size --;
    nodeMap.erase(ret);
    history[ret] = prevNode;
    return fnode;
}

FrontierNode* Frontier::find(Node* node){
    if(nodeMap.find(node) != nodeMap.end())
        return nodeMap[node];
    else
        return NULL;
}

void Frontier::update(FrontierNode* fnode){
    minNodeHeap.push(*fnode);
}
