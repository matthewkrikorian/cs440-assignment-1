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
    Node* start = maze->getStart();
    vector<Node*>* goals = maze->getGoals();
    Node* goal = goals->front();

    unordered_map<Node*, Node*> explored;

    Frontier frontier;
    frontier.push_back(start, NULL, manhattanDistance(start, goal));

    Node* cur = NULL;
    //Do search
    while(!frontier.empty()){
        if(method.compare("DFS") == 0){
            cur = frontier.pop_back(explored);
        }
        else if(method.compare("BFS") == 0){
            cur = frontier.pop_front(explored);
        }
        else if(method.compare("greedy") == 0){
            cur = frontier.pop_min(explored);
        }

        //cur = curFrontierNode->node;

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
                        frontier.push_back(neighbor, cur, manhattanDistance(cur, goal));
                    else {
                        // Update path costs if applicable
                        // if(found->pathCost > curFrontierNode->pathCost+1){
                        //     found->pathCost = curFrontierNode->pathCost+1
                        //     found->prevNode = cur;
                        //     frontier.update(found); //updates minNodeHeap
                        // }
                    }
                }

            }
        }
    }

    //backtracking
    while(cur != NULL){
        cur->visit();
        cur = explored[cur]; // go to previous
    }

    cout << explored.size() << " nodes explored during search.\n";

}

int main(int argc, char const *argv[]) {
    Maze* maze = new Maze("./mazes/1-1-big-maze.txt");
    search(maze, "greedy");
    maze->printSolution();
    return true;
}
