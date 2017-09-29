#ifndef NODE_H
#define  NODE_H

#include <vector>

class Node {

public:
    Node(int x, int y, int numDots, int dotsHash, int dotId = -1);
    bool isVisited();
    void visit();
    bool isGoal();
    int getX();
    int getY();
    int getDots();
    int getDotsTakenHash();
    int getDotId();
    void setTaken(int dotNumber);
    bool hasTaken(int dotNumber);

private:
    int x, y, numDots, dotId, dotsHash;
    bool visited;

};

#endif
