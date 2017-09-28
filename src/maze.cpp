#include "maze.h"

#include <iostream>
#include <fstream>
using namespace std;

Maze::Maze(string filename){
    ifstream input(filename);
    name = filename;

    w = 0;
    h = 0;

    string temp;
    numGoals = 0;
    //Get height and width of maze, count number of goals
    while(getline(input, temp)){
        if(w == 0){
            w = temp.length();
        }
        for(int i = 0; i < w; i++){
            if(temp[i] == '.') {
                numGoals ++;
            }
        }
        h++;
    }

    //Allocate 2d array to hold contents of file
    maze = new Node***[w];
    for(int i = 0; i < w; i++){
        maze[i] = new Node**[h];
        for(int j = 0; j < h ; j++){
            maze[i][j] = new Node*[numGoals];
        }
    }

    //Reset the seek position of the input stream
    input.clear();
    input.seekg(0, ios::beg);

    // Populate the maze array, record locations of start and goals
    int y = 0;
    while(getline(input, temp)){
        for(int x = 0; x < w; x++){
            //Don't create nodes for walls
            if(temp[x] != '%'){
                maze[x][y][0] = new Node(x, y, 0, temp[x] == '.');
            }
            else
                maze[x][y][0] = NULL;

            if(temp[x] == 'P')
                start = maze[x][y][0];
            for(int i = 1; i < numGoals; i++){
                maze[x][y][i] = NULL;
            }
        }
        y++;
    }

}


vector<Node*> Maze::getNeighbors(Node* cur){
    int x = cur->getX();
    int y = cur->getY();
    int dots = cur->getDots();
    vector<Node*> neighbors;

    if(x+1 < w && maze[x+1][y][0] != NULL && !cur->hasVisited(maze[x+1][y][0])){ //not a wall
        int numDots = dots + maze[x+1][y][0]->isGoal();
        if(maze[x+1][y][numDots] == NULL){ //does this state exist yet?
            maze[x+1][y][numDots] = new Node(x+1, y, numDots, false);
            maze[x+1][y][numDots]->setSpacesVisited(cur->getSpacesVisited());
            maze[x+1][y][numDots]->setVisited(maze[x+1][y][0]);
        }
        neighbors.push_back(maze[x+1][y][numDots]);
    }

    if(x-1 >= 0 && maze[x-1][y][0] != NULL && !cur->hasVisited(maze[x-1][y][0])){ //not a wall and unvisited
        int numDots = dots + maze[x-1][y][0]->isGoal();
        if(maze[x-1][y][numDots] == NULL){ //does this state exist yet?
            maze[x-1][y][numDots] = new Node(x-1, y, numDots, false); //create it
            maze[x-1][y][numDots]->setSpacesVisited(cur->getSpacesVisited()); //set spaces visited up til this space
            maze[x-1][y][numDots]->setVisited(maze[x-1][y][0]); //add self
        }
        neighbors.push_back(maze[x+1][y][numDots]);
    }

    if(y+1 < h && maze[x][y+1][0] != NULL && !cur->hasVisited(maze[x][y+1][0])){//not a wall and unvisited
        int numDots = dots + maze[x][y+1][0]->isGoal();
        if(maze[x][y+1][numDots] == NULL){ //does this state exist yet?
            maze[x][y+1][numDots] = new Node(x, y+1, numDots, false); //create it
            maze[x][y+1][numDots]->setSpacesVisited(cur->getSpacesVisited()); //set spaces visited up til this space
            maze[x][y+1][numDots]->setVisited(maze[x][y+1][0]); //add self
        }
        neighbors.push_back(maze[x][y+1][numDots]);
    }

    if(y-1 >= 0 && maze[x][y-1][0] != NULL && !cur->hasVisited(maze[x][y-1][0])){//not a wall and unvisited
        int numDots = dots + maze[x][y-1][0]->isGoal();
        if(maze[x][y-1][numDots] == NULL){ //does this state exist yet?
            maze[x][y-1][numDots] = new Node(x, y-1, numDots, false); //create it
            maze[x][y-1][numDots]->setSpacesVisited(cur->getSpacesVisited()); //set spaces visited up til this space
            maze[x][y-1][numDots]->setVisited(maze[x][y-1][0]); //add self
        }
        neighbors.push_back(maze[x][y-1][numDots]);
    }

    return neighbors;
}

Maze::~Maze(){
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            for(int k = 0; k < numGoals; k++){
                if(maze[i][j][k] != NULL)
                    delete maze[i][j][k];
            }
            delete[] maze[i][j];
        }
        delete[] maze[i];
    }
    delete[] maze;
}

Node* Maze::getStart(){
    return start;
}

bool Maze::isGoal(int x, int y){
    return maze[x][y][0]->isGoal();
}

int Maze::getNumGoals(){
    return numGoals;
}

void Maze::visit(Node* curNode){
    int x = curNode->getX();
    int y = curNode->getY();
    maze[x][y][0]->visit();
}

void Maze::printSolution(){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(maze[j][i][0] == NULL){
                cout << '%';
            }
            else if(maze[j][i][0] == start){
                cout << 'P';
            }
            else if(maze[j][i][0]->isVisited()){
                cout << '.';
            }
            else {
                cout << ' ';
            }
        }
        cout << '\n';
    }
}

string Maze::getName(){
    return name;
}
