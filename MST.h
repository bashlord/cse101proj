#include "common.h"
#include <map>
#include <stack>
#include <list>

#pragma once
using namespace std; 
class MST {
public:

	//stuff for dfs shortcuts


	int** adjacentMatrix;
	int** graph;
	int** minMatch;
	int* parent; //Array to store constructed MST
	int* key; //Key values used to pick minimum weight edge in cut
	bool* mstSet; //To represent set of vertices not yet included in MST
	int* neigh;
	int oddCount;
	
	int N; //the size of pointset
	int c = 0;
	int cost = 999999;
	int Eulercost;
	int* Degree;
	int* oddDegree;
	
//	void Graph(int** input,int size);
//	void printGraph();
	MST(int** adjacentMatrix, int size);
	~MST();
	
	int parentReturn(int i);

	//deliverable a
	void makeTree();
	void printMST();

	int* getMST();

	//deliverable c
	int* oddReturn();
	int oddCountReturn();
	void makeTSP1_5();
	void oddDegreeMaker();
	void printOdd();
	void makeOdds();
	
	float calMean(int option);
	float calStd(int option);
	

private:
	void minimumMatching();
	void combine();
	int minKey(int key[], bool mstSet[]);

};
