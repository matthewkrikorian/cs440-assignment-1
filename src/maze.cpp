#include "maze.h"

#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

Maze::Maze(string filename, string version){
    ifstream input(filename);
    this->name = filename;
    this->version = version;

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
    maze = new unordered_map<uint32_t, Node*>***[w];
    for(int i = 0; i < w; i++){
        maze[i] = new unordered_map<uint32_t, Node*>**[h];
        for(int j = 0; j < h ; j++){
            maze[i][j] = new unordered_map<uint32_t, Node*>*[numGoals];
        }
    }

    //Reset the seek position of the input stream
    input.clear();
    input.seekg(0, ios::beg);

    // Populate the maze array, record locations of start and goals
    int y = 0;
    int goalNum = 0;
    while(getline(input, temp)){
        for(int x = 0; x < w; x++){
            //Don't create nodes for walls
            if(temp[x] != '%'){
                maze[x][y][0] = new unordered_map<uint32_t, Node*>;
                if (temp[x] == '.') {
                    maze[x][y][0]->operator[](0) = new Node(x, y, 0, 0, goalNum++); //map all to 0 dots collected to begin
                    goals.push_back(maze[x][y][0]->at(0));
                }
                else {
                    maze[x][y][0]->operator[](0) = new Node(x, y, 0, 0); //map all to 0 dots collected to begin
                }

                for(int i = 1; i < numGoals; i++){
                    maze[x][y][i] = new unordered_map<uint32_t, Node*>;
                }
            }
            else {
                for(int i = 0; i < numGoals; i++){
                    maze[x][y][i] = NULL;
                }
            }
            if(temp[x] == 'P')
                start = maze[x][y][0]->at(0);
        }
        y++;
    }

}


vector<Node*> Maze::getNeighbors(Node* cur, int dots, uint32_t hash){
    int x = cur->getX();
    int y = cur->getY();
    vector<Node*> neighbors;

    if(x+1 < w && maze[x+1][y][0] != NULL){ //not a wall
        if(maze[x+1][y][dots]->find(hash) == maze[x+1][y][dots]->end()){ //does this state exist yet?
            maze[x+1][y][dots]->operator[](hash) = new Node(x+1, y, dots, hash, maze[x+1][y][0]->at(0)->getDotId());
        }
        neighbors.push_back(maze[x+1][y][dots]->at(hash));
    }

    if(x-1 >= 0 && maze[x-1][y][0] != NULL){ //not a wall//not a wall
        if(maze[x-1][y][dots]->find(hash) == maze[x-1][y][dots]->end()){ //does this state exist yet?
            maze[x-1][y][dots]->operator[](hash) = new Node(x-1, y, dots, hash, maze[x-1][y][0]->at(0)->getDotId());
        }
        neighbors.push_back(maze[x-1][y][dots]->at(hash));
    }

    if(y+1 < w && maze[x][y+1][0] != NULL){ //not a wall
        if(maze[x][y+1][dots]->find(hash) == maze[x][y+1][dots]->end()){ //does this state exist yet?
            maze[x][y+1][dots]->operator[](hash) = new Node(x, y+1, dots, hash, maze[x][y+1][0]->at(0)->getDotId());
        }
        neighbors.push_back(maze[x][y+1][dots]->at(hash));
    }

    if(y-1 >= 0 && maze[x][y-1][0] != NULL){ //not a wall//not a wall
        if(maze[x][y-1][dots]->find(hash) == maze[x][y-1][dots]->end()){ //does this state exist yet?
            maze[x][y-1][dots]->operator[](hash) = new Node(x, y-1, dots, hash, maze[x][y-1][0]->at(0)->getDotId());
        }
        neighbors.push_back(maze[x][y-1][dots]->at(hash));
    }

    return neighbors;
}

Maze::~Maze(){
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            for(int k = 0; k < numGoals; k++){
                if(maze[i][j][k] != NULL){
                    for (pair<const int, Node *> intNodePair : *maze[i][j][k]) {
                        delete get<1>(intNodePair);
                    }
                }
                else {
                    continue;
                }
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
vector<Node*> Maze::getGoals(){
    return goals;
}

int Maze::getNumGoals(){
    return numGoals;
}

void Maze::visit(Node* curNode){
    int x = curNode->getX();
    int y = curNode->getY();
    maze[x][y][0]->at(0)->visit();
}

bool Maze::canSetSymbol(Node* curNode){
    int x = curNode->getX();
    int y = curNode->getY();
    return maze[x][y][0]->at(0)->canSet();
}

void Maze::setSymbol(Node* curNode, int place){
    int x = curNode->getX();
    int y = curNode->getY();
    maze[x][y][0]->at(0)->setSymbol(place);
}

void Maze::printSolution(){
    if(version.compare("1.2") == 0){
            for(int i = 0; i < h; i++){
                for(int j = 0; j < w; j++){
                    if(maze[j][i][0] == NULL){
                        cout << '%';
                    }
                    else if(maze[j][i][0]->at(0) == start){
                        cout << 'P';
                    }
                    else if(maze[j][i][0]->at(0)->isGoal()){
                        cout << maze[j][i][0]->at(0)->getSymbol();
                    }
                    else {
                        cout << ' ';
                    }
                }
                cout << '\n';
            }
    }
    else if (version.compare("1.1") == 0){
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                if(maze[j][i][0] == NULL){
                    cout << '%';
                }
                else if(maze[j][i][0]->at(0) == start){
                    cout << 'P';
                }
                else if(maze[j][i][0]->at(0)->isVisited()){
                    cout << '.';
                }
                else {
                    cout << ' ';
                }
            }
            cout << '\n';
        }
    }
}

string Maze::getName(){
    return name;
}

string Maze::getVersion(){
    return version;
}
