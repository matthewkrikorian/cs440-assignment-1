#include "mst.h"

using namespace std;

int MST::manhattanDistance(Node* n1, Node* n2){
    return abs(n1->getX() - n2->getX()) + abs(n1->getY() - n2->getY());
}

MST::MST(const vector<Node*>& goals, int numDots){
    numGoals = goals.size();
    totalCost = 0;
    if(numGoals == 1){
        return;
    }
    dsets.addelements(numDots);

    for(int i = 0; i < numGoals; i++){
        for(int j = i+1; j < numGoals; j++){
            Edge* edge = new Edge;
            edge->v1 = goals[i];
            edge->v2 = goals[j];
            edge->length = manhattanDistance(goals[i], goals[j]);
            minEdgeHeap.push(edge);
        }
    }

    while(curVertices.size() != numGoals){
        Edge* minEdge = minEdgeHeap.top();
        minEdgeHeap.pop();
        if(dsets.find(minEdge->v1->getDotId()) != dsets.find(minEdge->v2->getDotId())){ //if the vertices aren't in the same set (same component)
            //then we can form an edge
            dsets.setunion(minEdge->v1->getDotId(), minEdge->v2->getDotId());
            totalCost += minEdge->length;
            curVertices.insert(minEdge->v1->getDotId());
            curVertices.insert(minEdge->v2->getDotId());
        }
        delete minEdge;
    }
    while(!minEdgeHeap.empty()){
        Edge* minEdge = minEdgeHeap.top();
        minEdgeHeap.pop();
        delete minEdge;
    }
}

int MST::getTotalCost(){
    return totalCost;
}
