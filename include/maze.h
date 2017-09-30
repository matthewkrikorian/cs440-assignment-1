#ifndef MAZE_H
#define  MAZE_H

#include "node.h"

#include <vector>
#include <unordered_map>
#include <string>

class Maze {

public:
    Maze(std::string filename, std::string version);
    ~Maze();
    Node* getStart();
    std::vector<Node*> getGoals();
    int getNumGoals();
    void printSolution();
    std::string getName();
    std::string getVersion();
    std::vector<Node*> getNeighbors(Node* cur, int numDots, uint32_t hash);
    void visit(Node* curNode);
    void setSymbol(Node* curNode, int place);
    bool canSetSymbol(Node* curNode);

private:
    std::string name, version;
    Node* start;
    std::vector<Node*> goals;
    std::unordered_map<uint32_t, Node*>**** maze;
    int w, h, numGoals;

};

#endif
