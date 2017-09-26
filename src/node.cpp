#include "node.h"

using namespace std;

Node::Node(int x, int y){
    this->x = x;
    this->y = y;
    this->neighbors = new std::vector<Node*>();
    this->visited = false;
}

Node::~Node(){
    delete neighbors;
}

vector<Node*>* Node::getNeighbors(){
    return this->neighbors;
}

void Node::addNeighbor(Node* neighbor){
    this->neighbors->push_back(neighbor);
}

bool Node::isVisited(){
    return this->visited;
}

void Node::visit(){
    this->visited = true;
}

int Node::getX(){
    return x;
}


int Node::getY(){
    return y;
}
