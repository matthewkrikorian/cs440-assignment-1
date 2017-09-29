#ifndef MAZE_H
#define  MAZE_H

#include "node.h"

#include <vector>
#include <unordered_map>
#include <string>

class Maze {

public:
    Maze(std::string filename);
    ~Maze();
    Node* getStart();
    int getNumGoals();
    void printSolution();
    std::string getName();
    std::vector<Node*> getNeighbors(Node* cur, int numDots, int hash);
    void visit(Node* curNode);

private:
    std::string name;
    Node* start;
    std::unordered_map<int, Node*>**** maze;
    int w, h, numGoals;

};

#endif
