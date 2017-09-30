#include <iostream>
#include <unordered_map>
#include <stdlib.h>

#include "maze.h"
#include "node.h"
#include "frontier.h"
#include "mst.h"

using namespace std;

unordered_map<uint32_t, int> memo;

int getMSTLength(Node* n, vector<Node*> goals){
    uint32_t hash = n->getDotsTakenHash();
    if(memo.find(hash) != memo.end()){
        //do nothing
    }
    else {
        uint32_t tempHash = hash;
        vector<Node*> dots;
        for(int i = 0; i < goals.size(); i++){
            if(!(tempHash & 1)){
                dots.push_back(goals[i]);
            }
            tempHash = tempHash >> 1;
        }
        MST mst(dots);
        memo[hash] = mst.getTotalCost();
    }
    return memo[hash];

}

void search(Maze* maze, string method){
    cout << "Starting " << method << " search on " << maze->getName() << '\n';
    Node* start = maze->getStart();
    vector<Node*> goals = maze->getGoals();
    Node* goal = goals[0];
    cout << getMSTLength(start, goals) << " length of MST \n";

    int goalDots = maze->getNumGoals();
    cout << "Goal size: " << goalDots << "\n";

    unordered_map<Node*, Node*> explored;

    Frontier frontier;
    frontier.push_back(start, NULL, goalDots, 0); //assume start is not a dot since 'P' != '.'

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
        int curDots = cur->getDots(); //get updated # of dots
        uint32_t hash = cur->getDotsTakenHash();
        if(cur->isGoal() && !cur->hasTaken(cur->getDotId())){ //Check if explored node has dot
            curDots += 1;
            hash += (1 << cur->getDotId());
        }

        // Reached goal
        if(curDots == goalDots){
            break;
        }
        else {
            // For each neighbor
            for(Node* neighbor : maze->getNeighbors(cur, curDots, hash)){
                // Must not be explored
                if(explored.find(neighbor) == explored.end()){
                    // Must not be on frontier (unless cur has lower path cost to it)
                    FrontierNode* found = frontier.find(neighbor);
                    if(found == NULL){ // can add to frontier
                        if(method.compare("A*") == 0){
                            //Only update path cost for A* search
                            if(maze->getVersion().compare("1.1")==0){
                                frontier.push_back(neighbor, cur, MST::manhattanDistance(neighbor, goal), curExploredNode->pathCost + 1);
                            }
                            else {
                                frontier.push_back(neighbor, cur, getMSTLength(neighbor, goals), curExploredNode->pathCost + 1);
                            }
                        }
                        else {
                            //Keep 0 path cost for everything else
                            if(maze->getVersion().compare("1.1")==0){
                                frontier.push_back(neighbor, cur, MST::manhattanDistance(neighbor, goal), 0);
                            }
                            else {
                                frontier.push_back(neighbor, cur, 0, 0);
                            }
                        }
                    }
                    else {
                        // Update path costs if applicable
                        if( method.compare("A*") == 0 && found->pathCost > curExploredNode->pathCost + 1 ){
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
    vector<Node*> solutionNodes;
    while(cur != NULL){
        sizeOfSolution += 1;
        solutionNodes.push_back(cur);
        cur = explored[cur]; //go to previous
    }
    int curDotsCollected = 1;
    vector<Node*>::reverse_iterator rit = solutionNodes.rbegin();
    for(; rit!= solutionNodes.rend(); ++rit){
        (*rit)->visit();
        if((*rit)->isGoal() && maze->canSetSymbol(*rit)){
            maze->setSymbol(*rit, curDotsCollected++);
        }
    }

    cout << explored.size() << " nodes explored during search.\n";
    cout << sizeOfSolution << " steps to reach goal.\n";

}

int main(int argc, char const *argv[]) {
    // Maze* maze1 = new Maze("./mazes/1-1-big-maze.txt");
    Maze* maze2 = new Maze("./mazes/1-2-tiny-search.txt", "1.2");
    // Maze* maze3 = new Maze("./mazes/1-1-big-maze.txt");
    Maze* maze4 = new Maze("./mazes/1-2-tiny-search.txt", "1.2");
    // search(maze1, "DFS");
    // maze1->printSolution();
    search(maze2, "BFS");
    maze2->printSolution();
    // search(maze3, "greedy");
    // maze3->printSolution();
    search(maze4, "A*");
    maze4->printSolution();
    // delete maze1;
    delete maze2;
    // delete maze3;
    delete maze4;
    return true;
}
