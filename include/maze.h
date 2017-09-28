#ifndef MAZE_H
#define  MAZE_H

#include "node.h"

#include <vector>
#include <string>

class Maze {

public:
    Maze(std::string filename);
    ~Maze();
    Node* getStart();
    int getNumGoals();
    void printSolution();
    std::string getName();
    bool isGoal(int x, int y);
    std::vector<Node*> getNeighbors(Node* cur);
    void visit(Node* curNode);

private:
    std::string name;
    Node* start;
    Node**** maze;
    int w, h, numGoals;

};

#endif
