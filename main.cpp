#include "common.h"
#include "point.h"
#include "MST.h"
#include "Minmatching/PerfectMatching.h"
#include <stdio.h>
#include <stdlib.h>
#include "tsp_2.h"
#include "tsp_15.h"

/*
This project is a starter code and wrappers for CSE101W15 Implementation project.

point.h - uniform random pointset generator

MST.h - minimum spanning tree

PerfectMatching.h - interface to min cost perfect matching code 

-------------------------------------
PerfectMatching is from the paper:

Vladimir Kolmogorov. "Blossom V: A new implementation of a minimum cost perfect matching algorithm."
In Mathematical Programming Computation (MPC), July 2009, 1(1):43-67.

sourcecode : pub.ist.ac.at/~vnk/software/blossom5-v2.05.src.tar.gz

*/

void LoadInput(int& node_num, int& edge_num, int*& edges, int*& weights, int** adjacentMatrix, int*& oddNodeArray) {
	int e = 0;
//	node_num = N;
//	edge_num = N*(N-1)/2 ; //complete graph

	
cout << "THIS IS COMING FROM INSIDE LOAD INPUT" << endl;
	edges = new int[2*edge_num];
	weights = new int[edge_num];

	for(int i = 0; i < node_num ; ++i) {
		for(int j = i+1 ; j< node_num ; ++j) {
			edges[2*e] = i;
			edges[2*e+1] = j;
			weights[e] = adjacentMatrix[oddNodeArray[i]][oddNodeArray[j]];
			e++;
		}
	}

	if (e != edge_num) { 
		cout<<"the number of edge is wrong-- Edgenum: "<< edge_num<< "   e-- " <<e<<endl;

		exit(1); 
	}
}

void PrintMatching(int node_num, PerfectMatching* pm, int*& oddNodeArray, int*& matching) {
	int i, j;
	int matchcount = 0;
//	int* edge = edges;
	matching = new int[node_num];

	for (i=0; i<node_num; i++) {
		j = pm->GetMatch(i);
		if (i < j){ 
			printf("%d %d\n", oddNodeArray[i], oddNodeArray[j]);
			matching[matchcount] = oddNodeArray[i];
			matchcount++;
			matching[matchcount] = oddNodeArray[j];
			matchcount++;
		}
		
	}
}

int main(int argc, char *argv[]) {
	set< pair<int,int> > generatedPointset;
	int** adjacentMatrix;
	int W, H, N;
	Point pointset;
	int* parentmst;
	

	if(argc != 4){
		cout << "                ╚(•⌂•)╝ Not enough arguments you dumb dumb (┛◉Д◉)┛彡┻━┻" << endl;
		exit(1);
	}

	W = atoi(argv[1]);
	H = atoi(argv[2]);
	N = atoi(argv[3]);

	cout<<"W: "<<W<<" H: "<<H<<" N:"<<N<<endl;

	pointset.generatePoint(W, H, N); //max(W,H,N) should be < 20000 because of memory limitation
	pointset.printPointset();

	generatedPointset = pointset.getPointset();
	adjacentMatrix = pointset.getAdjacentMatrix();

	//Deliverable A: From pointset and adjacentMatrix, you should construct MST with Prim or Kruskal
	MST mst(adjacentMatrix, N);
	mst.makeTree();
	mst.printMST();

	parentmst = mst.getMST();
	int* mstt;
	mstt = parentmst;

//	cout << "tsp constructor";
	tsp_2 tsp2(parentmst,adjacentMatrix, N);
//	cout <<"SECOND PRINT OF PARENTS"<<endl;
//	tsp2.printParent();
	
//	cout << "PRinting TSP2 " <<endl;

	
//	cout << "make edges for the tsp" << endl;
	for(int i =1;i<N;i++){
	int b = parentmst[i];
//	cout << "B HAS BEEN SET AS THE PARENT "<<  b << " of " << i << endl;
	tsp2.addEdge(b,i);
}
//	tsp2.printTSP2();

	mst.calMean(1);
	mst.calStd(1);
	
	mst.oddDegreeMaker();
	mst.printOdd();
	mst.makeOdds();

	//Deliverable B: Find TSP2 path from the constructed MST
	//You won't need any wrappers for B.
	cout <<"Calling DFSUTil " << endl;
	tsp2.DFSUtil();
	tsp2.calMean();
	tsp2.calStd();

	//Deliverable C: Find TSP1.5 path from the constructed MST
//	cout << "ODD COUNT: " << mst.oddCountReturn() << endl;	
	//Find the perfect minimum-weight matching

	int* matching;
 
	struct PerfectMatching::Options options;
//cout << "Variavles set"<<endl;
	int i, e, node_num = mst.oddCountReturn(), edge_num = node_num*(node_num-1)/2;
//cout << "NODE NUM: " <<  node_num<< endl;
	int* edges;
//cout << "EDGES SET"<<endl;
	int* weights;
	int* oddNodeArray = mst.oddReturn();
//cout << "PRE PERFECT MATCHING" <<endl;
	PerfectMatching *pm = new PerfectMatching(node_num, edge_num);
	cout <<" post perfect matchhing now into load input"<< endl;
	LoadInput(node_num, edge_num, edges, weights, adjacentMatrix, oddNodeArray);
//cout<< "Load Inputs \n"<<endl;
//cout << i<< " " << e<<" " << node_num << " " <<edge_num << " "<< endl;
	for (e=0; e<edge_num; e++) {
//cout << "INSIDE E FORLOOP" <<endl;
		pm->AddEdge(edges[2*e], edges[2*e+1], weights[e]);
//cout << "ADDEDGE COMPLETE" << endl;
	}

	pm->options = options;
	pm->Solve();

	double cost = ComputePerfectMatchingCost(node_num, edge_num, edges, weights, pm);
	printf("Total cost of the perfect min-weight matching = %.1f\n", cost);
	
	PrintMatching(node_num, pm, oddNodeArray, matching);
	for(int x = 0; x < node_num; x++)
		cout << "MATCH SET OUTPUT: " << matching[x] << endl;

	tsp_15 tsp15(mstt,adjacentMatrix, N);
//	cout <<"SECOND PRINT OF PARENTS"<<endl;
//	tsp2.printParent();
	
//	cout << "PRinting TSP2 " <<endl;

	
//	cout << "make edges for the tsp" << endl;
	for(int i =1;i<N;i++){
	int b = mstt[i];
//	cout << "B HAS BEEN SET AS THE PARENT "<<  b << " of " << i << endl;
	tsp15.addEdge(b,i);
}

cout << "beforeoods"<<endl;	
cout<<"after odds"<<endl;
	//Deliverable B: Find TSP2 path from the constructed MST
	//You won't need any wrappers for B.
	cout <<"Calling DFSUTil " << endl;
	tsp15.DFSUtil();
	tsp15.calMean();
	tsp15.calStd();

	delete pm;
	delete [] edges;
	delete [] weights;
	
	return 0;
}
