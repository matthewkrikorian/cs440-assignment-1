#include <iostream>
#include <unordered_map>
#include <stdlib.h>

#include "maze.h"
#include "node.h"
#include "frontier.h"

using namespace std;

int manhattanDistance(Node* n1, Node* n2){
    return abs(n1->getX() - n2->getX()) + abs(n1->getY() - n2->getY());
}

void search(Maze* maze, string method){
    cout << "Starting " << method << " search on " << maze->getName() << '\n';
    Node* start = maze->getStart();
    vector<Node*>* goals = maze->getGoals();
    Node* goal = goals->front();

    unordered_map<Node*, Node*> explored;

    Frontier frontier;
    frontier.push_back(start, NULL, manhattanDistance(start, goal), 0);

    Node* cur = NULL;
    FrontierNode* curExploredNode = NULL;
    //Do search
    while(!frontier.empty()){
        if(method.compare("DFS") == 0){
            curExploredNode = frontier.pop_back(explored);
        }
        else if(method.compare("BFS") == 0){
            curExploredNode = frontier.pop_front(explored);
        }
        else if(method.compare("greedy") == 0 || method.compare("A*") == 0){
            //Get the min on the frontier based on heuristic/heuristic+pathCost (depending on method)
            curExploredNode = frontier.pop_min(explored);
        }

        cur = curExploredNode->node;

        // Reached goal
        if(cur == goal){
            break;
        }
        else {
            // For each neighbor
            for(Node* neighbor : *(cur->getNeighbors())){
                // Must not be explored
                if(explored.find(neighbor) == explored.end()){
                    // Must not be on frontier (unless cur has lower path cost to it)
                    FrontierNode* found = frontier.find(neighbor);
                    if(found == NULL) // can add to frontier
                        if(method.compare("A*") == 0){
                            //Only update path cost for A* search
                            frontier.push_back(neighbor, cur, manhattanDistance(neighbor, goal), curExploredNode->pathCost + 1);
                        }
                        else {
                            //Keep 0 path cost for everything else
                            frontier.push_back(neighbor, cur, manhattanDistance(neighbor, goal), 0);
                        }
                    else {
                        // Update path costs if applicable
                        if( method.compare("A*") == 0 && found->pathCost > curExploredNode->pathCost + 1){
                            found->pathCost = curExploredNode->pathCost+1;
                            found->prevNode = cur;
                            frontier.update(found); //updates minNodeHeap
                        }
                    }
                }

            }
        }
        delete curExploredNode;
        curExploredNode = NULL;
    }
    if(curExploredNode != NULL){
        delete curExploredNode;
    }

    int sizeOfSolution = -1;

    //backtracking
    while(cur != NULL){
        sizeOfSolution += 1;
        cur->visit();
        cur = explored[cur]; // go to previous
    }

    cout << explored.size() << " nodes explored during search.\n";
    cout << sizeOfSolution << " steps to reach goal.\n";

}

int main(int argc, char const *argv[]) {
    Maze* maze1 = new Maze("./mazes/1-1-big-maze.txt");
    Maze* maze2 = new Maze("./mazes/1-1-big-maze.txt");
    Maze* maze3 = new Maze("./mazes/1-1-big-maze.txt");
    Maze* maze4 = new Maze("./mazes/1-1-big-maze.txt");
    search(maze1, "DFS");
    maze1->printSolution();
    search(maze2, "BFS");
    maze2->printSolution();
    search(maze3, "greedy");
    maze3->printSolution();
    search(maze4, "A*");
    maze4->printSolution();
    delete maze1;
    delete maze2;
    delete maze3;
    delete maze4;
    return true;
}
