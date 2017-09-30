#include "dsets.h"

void DisjointSets::addelements(int num){
	for(int i = 0; i < num; i++){
		uptree.push_back(-1);
	} 
}

int DisjointSets::find(int elem){
	if(uptree[elem] >= 0){
		uptree[elem] = find(uptree[elem]);
		return uptree[elem];
	}
	else {
		return elem;
	}
}

void DisjointSets::setunion(int a, int b){
	int rootA = find(a);
	int rootB = find(b);
	int sizeA = -uptree[rootA];
	int sizeB = -uptree[rootB];
	if(sizeA < sizeB){
		uptree[rootA] = rootB;
		uptree[rootB] -= sizeA;
	}
	else {
		uptree[rootB] = rootA;
		uptree[rootA] -= sizeB;
	}
}
