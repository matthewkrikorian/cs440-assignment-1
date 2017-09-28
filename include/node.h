#ifndef NODE_H
#define  NODE_H

#include <unordered_set>

class Node {

public:
    Node(int x, int y, int numDots, bool goal);
    bool isVisited();
    void visit();
    bool isGoal();
    int getX();
    int getY();
    int getDots();
    bool hasVisited(Node* node);
    void setVisited(Node* node);
    void setSpacesVisited(std::unordered_set<Node*> otherSpacesVisited);
    std::unordered_set<Node*> getSpacesVisited();

private:
    int x, y, numDots;
    bool visited, goal;
    std::unordered_set<Node*> spacesVisited;

};

#endif
