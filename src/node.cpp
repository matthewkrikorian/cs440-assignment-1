#include "node.h"

using namespace std;

Node::Node(int x, int y, int numDots, int dotsHash, int dotId){
    this->x = x;
    this->y = y;
    this->dotId = dotId;
    this->numDots = numDots;
    this->dotsHash = dotsHash;
    this->visited = false;
}

bool Node::isVisited(){
    return this->visited;
}

void Node::visit(){
    this->visited = true;
}

bool Node::isGoal(){
    return this->dotId != -1;
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

int Node::getDotId(){
    return dotId;
}

void Node::setTaken(int dotNumber){
    if(dotId == -1) return;
    this->dotsHash += 1 << dotNumber; //bit shifting for fast powers of 2
    this->numDots += 1;
}

bool Node::hasTaken(int dotNumber){
    if(dotId == -1) return false;
    return this->dotsHash & (1 << dotNumber); //bit shifting for fast powers of 2
}

int Node::getDotsTakenHash(){
    return this->dotsHash;
}
