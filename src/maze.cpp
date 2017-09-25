#include "maze.h"

#include <iostream>
#include <fstream>
using namespace std;

Maze::Maze(string filename){
    ifstream input(filename);

    w = 0;
    h = 0;

    string temp;
    //Get height and width of maze, count number of goals
    while(getline(input, temp)){
        if(w == 0){
            w = temp.length();
        }
        h++;
    }

    //Allocate 2d array to hold contents of file
    maze = new Node**[w];
    for(int i = 0; i < w; i++){
        maze[i] = new Node*[h];
    }

    //Reset the seek position of the input stream
    input.clear();
    input.seekg(0, ios::beg);

    goals = new vector<Node*>();

    // Populate the maze array, record locations of start and goals
    int y = 0;
    while(getline(input, temp)){
        for(int x = 0; x < w; x++){
            //Don't create nodes for walls
            if(temp[x] != '%')
                maze[x][y] = new Node(x, y);
            else
                maze[x][y] = NULL;

            if(temp[x] == '.')
                goals->push_back(maze[x][y]);

            if(temp[x] == 'P')
                start = maze[x][y];
        }
        y++;
    }

    //Create graph
    for(int i = 0; i < w; i ++){
        for(int j = 0; j < h; j++){
            if(maze[i][j] == NULL)
                continue;

            if(i - 1 >= 0 && maze[i-1][j] != NULL)
                maze[i][j]->addNeighbor(maze[i-1][j]);

            if(i + 1 < w && maze[i+1][j] != NULL)
                maze[i][j]->addNeighbor(maze[i+1][j]);

            if(j - 1 >= 0 && maze[i][j-1] != NULL)
                maze[i][j]->addNeighbor(maze[i][j-1]);

            if(j+1 < h && maze[i][j+1] != NULL)
                maze[i][j]->addNeighbor(maze[i][j+1]);

        }
    }

}

Node* Maze::getStart(){
    return start;
}

vector<Node*>* Maze::getGoals(){
    return goals;
}

void Maze::printSolution(){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(maze[j][i] == NULL){
                cout << '%';
            }
            else if(maze[j][i] == start){
                cout << 'P';
            }
            else if(maze[j][i]->isVisited()){
                cout << '.';
            }
            else {
                cout << ' ';
            }
        }
        cout << '\n';
    }
}
