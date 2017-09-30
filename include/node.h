#ifndef NODE_H
#define  NODE_H

#include <vector>
#include <stdint.h>

class Node {

public:
    Node(int x, int y, int numDots, uint32_t dotsHash, int dotId = -1);
    bool isVisited();
    void visit();
    bool isGoal();
    int getX();
    int getY();
    int getDots();
    uint32_t getDotsTakenHash();
    int getDotId();
    void setTaken(int dotNumber);
    bool hasTaken(int dotNumber);
    void setSymbol(int place);
    char getSymbol();
    bool canSet();

private:
    int x, y, numDots, dotId;
    uint32_t dotsHash;
    char symbol;
    bool visited, notSet;
    static const unsigned char* symbols;

};

#endif
