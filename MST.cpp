#include "MST.h"

MST::MST(int** input, int size) {
	adjacentMatrix = input;
	N = size;
	key = new int[size];   
    mstSet = new bool[size];  
	parent = new int[size];
	Degree = new int[size];

	
}
/*
void MST::Graph(int** input, int size){
	graph = input;
	for(int i=0; i<size;i++){
		for(int j = 0; j<size;j++){
			graph[i][j] = 0;
		}
	}
}
void MST::printGraph(){
	 cout<<"adjacency matrix: "<<endl;
	 for(int i=0; i<N ; ++i) {
		 for(int j=0; j<N; ++j) {
			 cout<<graph[i][j]<<"  ";
}
		cout<<endl;

}
}
*/

MST::~MST() {

}

int* MST::getMST(){

return parent;
}

//use Prim's algorithm or Kruskal algorithm. Copied from 'http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/'
void MST::makeTree() { 
     // Initialize all keys as INFINITE
	bool noNext = false;
     for (int i = 0; i < N; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < N-1; count++)
     {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
//		cout << u << " - ";	

        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < N; v++){
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if adjacentMatrix[u][v] is smaller than key[v]
		//	int g = adjacentMatrix[u][v];
          if (adjacentMatrix[u][v] && mstSet[v] == false && adjacentMatrix[u][v] <  key[v]){
             parent[v]  = u, key[v] = adjacentMatrix[u][v];
		//	cout <<"SOMETHING FUCKING HAPPENS IN THE DFS " <<endl;
    	//	cout << key[v] << endl; 
		  }
		//	graph[u][v] = 1;
		}
	}
}

// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int MST::minKey(int key[], bool mstSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
   for (int v = 0; v < N; v++){
     if (mstSet[v] == false && key[v] < min){
         min = key[v], min_index = v;
}
 }
   return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void MST::printMST() {
	cout<<endl;
	cout<<"Minimum spanning tree from the adjacency matrix"<<endl;
	cout<<"Edge   Weight"<<endl;
	for (int i = 1; i < N; i++) {
		cout<<parent[i]<<" - "<<i<<"  "<<adjacentMatrix[i][parent[i]]<<endl;
	}
}

int MST::parentReturn(int i){
		return parent[i];
	}

int* MST::oddReturn(){
		return oddDegree;	
}

int MST::oddCountReturn(){
		return oddCount;
}

void MST::oddDegreeMaker(){
//	cout<< "Odd Degree 1st forloop \n " << endl;
	for(int i = 0; i < N; i++){
		int j = 1;
		int count = 1;
//		cout<< "While loop \n" << endl;
		while (j<N){
//			cout << N << "Inner if statement \n" << endl;
			if(parent[j] == i){
			 count++;
			}
			j++;
		}
		Degree[i] = count;
	}
}

void MST::printOdd(){
	for(int i = 0; i <N; i++){
		if(i == 0) Degree[0] = Degree[0] - 1;{
	//	cout << "Vertice Number: " << i << " Verticie Weight :" << Degree[i] << endl;
		if(Degree[i]%2) oddCount++;

		}
	//	cout << "ODD COUNT: " << oddCount<<endl;
	}
}

void MST::makeOdds(){
	oddDegree = new int[oddCount];
	stack<int> odds;
	
		for(int j = 0; j < N;j++){
			if(Degree[j]%2 == 1){
				odds.push(j);
				Degree[j] = 0;
			}
		}
		while(!odds.empty()){
			//int top;
			//odds.pop();
			for(int i = 0; i <oddCount;i++){
				oddDegree[i] = odds.top();
				odds.pop();
			}
			//odds.pop();
		}
		for(int a = 0; a <oddCount;a++)
			cout << "ODD VERTEX: " << oddDegree[a] << endl;
}



	/*	for(int i = 0; i<N;i++){
			if(Degree[i]%2)
				oddDegree[i] = Degree[i]
		}
*/


//calculate mean of all edges in the MST
float MST::calMean(int option) {
	float mean = 0.0;

	if(option == MST_1) {
		for(int i=1; i<N; i++){
		//	cout << adjacentMatrix[i][parent[i]] << "\n" << endl;
			mean = mean + adjacentMatrix[i][parent[i]];
		}
	//	mean = mean/(N-1);

	}else if(option == TSP2) {

	} else if(option == TSP1_5) {

	}
	cout<< "Oh Haaaaai look its the mean (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ~~~~~~~~~~~~~~~" <<  mean << endl;
	cout<< "\n";

	return mean;
}

//calculate standard deviation of all edges in the MST
float MST::calStd(int option) {
	float std = 0.0;
	float mean = 0.0;

	if(option == MST_1) {
		//calculate
		for(int i=1; i<N; i++){
			mean = mean + adjacentMatrix[i][parent[i]];
		}
		mean = (mean/N);
		for(int j = 1; j < N; j++){
			std += (adjacentMatrix[j][parent[j]] - mean)*(adjacentMatrix[j][parent[j]] - mean);
		}

		std = sqrt(std);
		cout << "YOU GOT AN STD ~~~~~ " << std << "\n"<< endl;
		return std;

	}else if(option == TSP2) {

	} else if(option == TSP1_5) {

	}

	return std;
}

/*void MST::makeTSP2() {
	//make a Eulerian tour by DFS
	int a[N];
	a[0] = 0;
	a[N] = N-1;
	
    	

	
	cout << "Min Cost::::::::::::::::::::=====~~~~~~ "<< cost <<endl;
}
void MST::DFS(){
  // Initialize all keys as INFINITE
	bool noNext = false;
     for (int i = 0; i < N; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < N-1; count++)
     {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
		if(neigh[u] == 1) mystack.push(u);
		cout << u << " - ";	
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < N; v++){
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if adjacentMatrix[u][v] is smaller than key[v]
		//	int g = adjacentMatrix[u][v];
          if (adjacentMatrix[u][v] && mstSet[v] == false && adjacentMatrix[u][v] <  key[v]){
             parent[v]  = u, key[v] = adjacentMatrix[u][v];
		//	cout <<"SOMETHING FUCKING HAPPENS IN THE DFS " <<endl;
    	//	cout << key[v] << endl; 
		  }
		//	graph[u][v] = 1;
		}
	}
	int a = minKey(key,mstSet);
	mystack.push(a);

	

	
	
}


void MST::printDFS(){
		cout << "\n PRINTING THE MUTHEFUKIN DFS~~" << endl;
		while(!mystack.empty()){
			cout << " " << mystack.top();
			mystack.pop();

}
}
*/

void MST::makeTSP1_5() {
	
	//construct minimum-weight-matching for the given MST
	minimumMatching();

	//make all edges has even degree by combining mimimum-weight matching and MST
	combine();

	//calculate heuristic TSP cost 
}

void MST::minimumMatching() { //if you choose O(n^2)
	//find minimum-weight matching for the MST. 
	
	//you should carefully choose a matching algorithm to optimize the TSP cost.
}

void MST::combine() {
	//combine minimum-weight matching with the MST to get a multigraph which has vertices with even degree
}
/*
void MST::hasNext(int size){
	neigh = new int[size];
	int zerocount = 0;
	for(int a = 1; a<size; a++){
		if(0 == parent[a])	zerocount++;
	}
	neigh[0] = zerocount;

	for(int j = 1; j <size;j++){
		int count = 1;
		for(int i = 1; i <size; i++){
			if(j == parent[i]) count++;	
		}
		neigh[j] = count;
	}

	for(int b = 0; b<N; b++)
		cout << "Vertice " << b << " has a neighbor count of " << neigh[b]<< endl;
}*/
