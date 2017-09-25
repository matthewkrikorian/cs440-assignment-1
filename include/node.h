#ifndef NODE_H
#define  NODE_H

#include <vector>

class Node {

public:
    Node(int x, int y);
    std::vector<Node*>* getNeighbors();
    void addNeighbor(Node*);

private:
    int x, y;
    std::vector<Node*>* neighbors;

};

#endif
