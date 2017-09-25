#include <iostream>
#include <unordered_map>

#include "maze.h"
#include "node.h"
#include "frontier.h"

using namespace std;

void search(Maze* maze, string method){
    Node* start = maze->getStart();
    vector<Node*>* goals = maze->getGoals();
    Node* goal = goals->front();

    unordered_map<Node*, Node*> explored;

    Frontier frontier;
    frontier.push_back(start, NULL);

    Node* cur = NULL;
    //Do search
    while(!frontier.empty()){
        if(method.compare("DFS") == 0){
            cur = frontier.pop_back(explored);
        }
        else if(method.compare("BFS") == 0){
            cur = frontier.pop_front(explored);
        }

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
                        frontier.push_back(neighbor, cur);
                    else{
                        //nothing for now, check path cost for A* later
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
    search(maze, "DFS");
    maze->printSolution();
    return true;
}
