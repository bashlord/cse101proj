#include "common.h"
#include <map>
#include <stack>
#include <list>

#pragma once
using namespace std;

class tsp_2 {

//stack<int> mystack;
//int* parentMst;
int V;
list<int> *adj;
int* parentMst;
//int DFSUtil();
public:
	stack <int>edgedistances;
	stack<int> mystack;
//	int* parentMst;

	bool* isVisited;

	int totaldistance;
//	list<int> *adj;
	int DFSUtil();
	int N;
	int** adjacentMatrix;

	tsp_2(int* parentmst, int** input, int size);
	~tsp_2();
	
	void addEdge(int u, int v);
	void DFS(int v);

	void printTSP2();
	void printParent();

	float calMean();
	float calStd();
	

	
	
	

};


 
