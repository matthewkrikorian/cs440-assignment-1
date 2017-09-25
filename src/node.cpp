#include "node.h"

using namespace std;

Node::Node(int x, int y){
    this->x = x;
    this->y = y;
    this->neighbors = new std::vector<Node*>();
}

vector<Node*>* Node::getNeighbors(){
    return this->neighbors;
}

void Node::addNeighbor(Node* neighbor){
    this->neighbors->push_back(neighbor);
}
