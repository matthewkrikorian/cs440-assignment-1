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
    std::vector<Node*>* getGoals();
    void printSolution();
    std::string getName();

private:
    std::string name;
    Node* start;
    std::vector<Node*>* goals;
    Node*** maze;
    int w, h;

};

#endif
