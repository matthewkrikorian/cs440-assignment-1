#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <limits.h>

#include "maze.h"
#include "node.h"
#include "frontier.h"
#include "mst.h"

using namespace std;

unordered_map<uint32_t, int> memo;


int getNearestNeighborDistance(Node* n, vector<Node*> goals){
    uint32_t hash = n->getDotsTakenHash();
    uint32_t tempHash = hash;
    int numDots = goals.size();
    //Compute min dist from cur node to dots remaining
    int minDist = INT_MAX;
    for(int i = 0; i< numDots; i++){
        if(!(tempHash & 1)){
            int dist = MST::manhattanDistance(n, goals[i]);
            if(dist < minDist){
                minDist = dist;
            }
        }
        tempHash = tempHash >> 1;
    }
    return minDist;
}

int getMSTLength(Node* n, vector<Node*> goals){
    uint32_t hash = n->getDotsTakenHash();
    uint32_t tempHash = hash;
    int numDots = goals.size();
    vector<Node*> dots;
    dots.push_back(n);
    for(int i = 0; i < numDots; i++){
        if(!(tempHash & 1)){
            dots.push_back(goals[i]);
        }
        tempHash = tempHash >> 1;
    }
    MST mst(dots, numDots);
    int val = mst.getTotalCost();
    return val + getNearestNeighborDistance(n, goals);
}

void search(Maze* maze, string method){
    cout << "Starting " << method << " search on " << maze->getName() << '\n';
    Node* start = maze->getStart();
    vector<Node*> goals = maze->getGoals();
    Node* goal = goals[0];

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
        else if(method.compare("greedy") == 0 || method.compare(0, 2, "A*") == 0){
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
                        else if(method.compare(0, 2, "A*") == 0){ //suboptimal search
                            if(maze->getVersion().compare("1.1")==0){
                                frontier.push_back(neighbor, cur, MST::manhattanDistance(neighbor, goal), curExploredNode->pathCost + 1);
                            }
                            else {
                                frontier.push_back(neighbor, cur, getNearestNeighborDistance(neighbor, goals), curExploredNode->pathCost + 1);
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
                        if( method.compare(0, 2, "A*") == 0 && found->pathCost > curExploredNode->pathCost + 1 ){
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
        else if( !(*rit)->isGoal() && maze->getStyle().compare("dots") == 0 ) {
            maze->setSymbol(*rit, -1);
        }
    }

    cout << explored.size() << " nodes explored during search.\n";
    cout << sizeOfSolution << " steps to reach goal.\n";

}

int main(int argc, char const *argv[]) {
    /*******************************************************
    MP 1.1 - Uncomment below to run
    *******************************************************/
    // Maze* maze1 = new Maze("./mazes/1-1-big-maze.txt", "1.1");
    // Maze* maze2 = new Maze("./mazes/1-1-big-maze.txt", "1.1");
    // Maze* maze3 = new Maze("./mazes/1-1-big-maze.txt", "1.1");
    // Maze* maze4 = new Maze("./mazes/1-1-big-maze.txt", "1.1");
    //
    // search(maze1, "DFS");
    // maze1->printSolution();
    // search(maze2, "BFS");
    // maze2->printSolution();
    // search(maze3, "greedy");
    // maze3->printSolution();
    // search(maze4, "A*");
    // maze4->printSolution();
    //
    // delete maze1;
    // delete maze2;
    // delete maze3;
    // delete maze4;

    /*******************************************************
    MP 1.2 - Uncomment below to run
    *******************************************************/

    // Maze* maze1 = new Maze("./mazes/1-2-medium-search.txt", "1.2");
    Maze* maze2 = new Maze("./mazes/1-2-tiny-search.txt", "1.2", "dots");

    // search(maze1, "BFS");
    // maze1->printSolution();
    search(maze2, "A*");
    maze2->printSolution();

    // delete maze1;
    delete maze2;


    /*******************************************************
    MP 1.2 suboptimal tests - Uncomment below to run
    *******************************************************/

    // Maze* maze1 = new Maze("./mazes/1-2-tiny-search.txt", "1.2");
    // Maze* maze2 = new Maze("./mazes/1-2-tiny-search.txt", "1.2");
    //
    // search(maze1, "BFS");
    // maze1->printSolution();
    // search(maze2, "A*suboptimal");
    // maze2->printSolution();
    //
    // delete maze1;
    // delete maze2;

    /*******************************************************
    MP 1ExtraCredit- Uncomment below to run
    *******************************************************/

    // Maze* maze1 = new Maze("./mazes/bigDots.txt", "1.1");
    // search(maze1, "A*suboptimal");
    // maze1->printSolution();
    // delete maze1;


    return true;
}
