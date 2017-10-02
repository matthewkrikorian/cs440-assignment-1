#include "node.h"

using namespace std;

static const unsigned char symbolArray[] = {'0', '1', '2', '3', '4', '5', '6',
                                            '7', '8', '9', 'a', 'b', 'c', 'd',
                                            'e', 'f', 'g', 'h', 'i', 'j', 'k',
                                            'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                            's', 't', 'u', 'v', 'w', 'x', 'y',
                                            'z', 'A', 'B', 'C', 'D', 'E', 'F',
                                            'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                            'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                                            'U', 'V', 'W', 'X', 'Y', 'Z'};
const unsigned char* Node::symbols = symbolArray;

Node::Node(int x, int y, int numDots, uint32_t dotsHash, int dotId){
    this->x = x;
    this->y = y;
    this->dotId = dotId;
    this->numDots = numDots;
    this->dotsHash = dotsHash;
    this->visited = false;
    this->symbol = ' ';
    this->notSet = true;
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

uint32_t Node::getDotsTakenHash(){
    return this->dotsHash;
}

void Node::setSymbol(int place){
    if(notSet) {
        if(place == -1){
            this->symbol = '.';
            notSet = false;
            return;
        }
        this->symbol = symbols[place];
        notSet = false;
    }
}

bool Node::canSet(){
    return notSet;
}

char Node::getSymbol(){
    return this->symbol;
}
