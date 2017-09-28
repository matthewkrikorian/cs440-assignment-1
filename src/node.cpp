#include "node.h"

using namespace std;

Node::Node(int x, int y, int numDots, bool goal){
    this->x = x;
    this->y = y;
    this->numDots = numDots;
    this->goal = goal;
    this->visited = false;
}

bool Node::isVisited(){
    return this->visited;
}

void Node::visit(){
    this->visited = true;
}

bool Node::isGoal(){
    return this->goal;
}

int Node::getX(){
    return x;
}

int Node::getY(){
    return y;
}

int Node::getDots(){
    return numDots;
}

bool Node::hasVisited(Node* node){
    return spacesVisited.find(node) != spacesVisited.end();
}

void Node::setVisited(Node* node){
    spacesVisited.insert(node);
}

void Node::setSpacesVisited(unordered_set<Node*> otherSpacesVisited){
    spacesVisited = otherSpacesVisited;
}

unordered_set<Node*> Node::getSpacesVisited(){
    return spacesVisited;
}
