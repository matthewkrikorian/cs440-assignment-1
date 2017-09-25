#ifndef NODE_H
#define  NODE_H

#include <vector>

class Node {

public:
    Node(int x, int y);
    std::vector<Node*>* getNeighbors();
    void addNeighbor(Node*);
    bool isVisited();
    void visit();

private:
    int x, y;
    std::vector<Node*>* neighbors;
    bool visited;

};

#endif
