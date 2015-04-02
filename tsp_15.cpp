#include "tsp_15.h"

tsp_15::tsp_15(int* parentmst, int** input,  int size){
	this->parentMst = parentmst;
	this->adjacentMatrix = input;
	this->V = size;	
	adj = new list<int>[V];
	isVisited = new bool[size];

//	for(int i = 1; i<V; i++)
//		cout << "Parentmst: " << parentMst[i] << " i: " << i;

	cout << endl;
}

void tsp_15::printParent(){

		for(int i = 1; i<V; i++)
		cout << "Parentmst: " << parentMst[i] << " i: " << i;


}

tsp_15::~tsp_15(){}



void tsp_15::addEdge(int u, int v){

		adj[u].push_back(v);

}

int tsp_15::DFSUtil(){
	int distance = 0;
	int shortcutcount = 0;
	int shortt;
	bool shortflag =  false;
	bool cutflag = false;
	int cut;
	int node;
	int top;
	int edgecounter = 0;
	double f = .825;

	for (int i = 0; i < V; i++)
         isVisited[i] = false;
cout<<"util is entered"<<endl;
	isVisited[0] = false;
	mystack.push(0);
	while(!mystack.empty()){
	cout <<"inside while loop"<<endl;
		node = mystack.top();



		if(!isVisited[node] && shortflag){
	//		cout << "SHORTCUTCOUNT IS DONE" << endl;
			distance = distance + adjacentMatrix[shortt][node];
			edgedistances.push(adjacentMatrix[shortt][node]);
			edgecounter++;
		
	//		cout << "SHORTCUTCOUNT IS DONE DISTANCE: " << adjacentMatrix[shortt][node]<< endl;
	//		cout<< "DISTANCE AFTER SHORTCUT " << distance << endl;
		
			shortflag = false;
			cutflag = false;
			shortcutcount = 0;
			isVisited[node] = true;
			//	while(mystack.size() != 1)
			//		mystack.pop();
		}
	//	cout << mystack.size()<<endl;	
		if(mystack.empty()) break;
	
	//	cout << "EDGE COUNT: " << edgecounter <<  " V: " << V<<endl;
	//	cout << "ENTERING EDGECOUNT CHECK " << endl;	
		if(edgecounter == (V-18)){
	//		cout << "# of edges is V-1" <<endl;
			distance = distance + adjacentMatrix[0][node];
	//		cout << "FINAL EDGE DISTANCE: " <<adjacentMatrix[0][node] << endl;
			break;
			while(!mystack.empty()){
			//	cout<< "POPPIN THE STACK FINAL" << mystack.size()<< endl;
				mystack.pop();
	//			cout<< "POPPIN THE STACK FINAL" << mystack.size()<< endl;

			}
		}
	
		
//cout << "EDGE CHECKER OVER"<< endl;	
		if( adj[node].empty()){
			top = mystack.top();
			mystack.pop();
			isVisited[node] = true;
	//		cout << "POPPED VERTEX " << top<<" SIZE OF STACK AFTER POP -------> " << mystack.size()<< endl;
 	//		cout<< "INSIDE DFSUTIL NO NEIGHBORS "<<endl;
	
			if(!shortflag){
	//			cout<<"SHORT FLAG SET " <<endl;
				edgecounter++;
				distance = distance +  adjacentMatrix[node][parentMst[node]];
				edgedistances.push(adjacentMatrix[node][parentMst[node]]);
	//			cout << "----------DISTANCE AFTER SHORTFLAG SET ------" << distance<< "~~ ADDED DISTANCE~~ " <<  adjacentMatrix[node][parentMst[node]]<< endl;
				shortt = top;						
				shortflag = true;
				shortcutcount++;
				
			}
	
	
/*
				else if(!cutflag){
					cout << "CUT FLAG IS SET" << endl;
					cut = top;
					cutflag = true;
					shortcutcount++;
				}*/
			
		}	
		else{
			//isVisited[node = true;
			if(node != 0 ){
				if(!isVisited[node]){
					distance = distance + adjacentMatrix[node][parentMst[node]];
					edgedistances.push(adjacentMatrix[shortt][node]);
					edgecounter++;
	//				cout << "------DISTANCE AFTER NODE ADDED THAT HAD NEIGHBOR---- " << distance << "  ADDED DISTANCE " << adjacentMatrix[node][parentMst[node]] << endl;
				isVisited[node] = true;
				}
			}
	//		cout << node << " has this many children>" <<adj[node].size() <<endl;
			list<int>::iterator i;	
		 	for(i = adj[node].begin(); i != adj[node].end(); ++i){
					//if(i != NULL)
					mystack.push(*i);
			//	isVisited[*i] = true;
				//	adj[node].pop_front();
				//	distance = distance + adjacentMatrix[node][*i];
				//	edgedistances.push(adjacentMatrix[shortt][cut]);
				//	cout << "CURRENT DISTANCE: " << distance << endl;
	//				cout << node << " has size " << adj[node].size() << " current CHILD OF NODE---- " << *i << endl;
					adj[node].pop_front();

			}	
		}
	}
		distance = f*distance;
		cout<< "THE TSP2 DISTANCE: " << distance<<  endl;
		totaldistance = distance;
		return distance;

	  
}


void tsp_15::printTSP2(){
	for(int j = 0; j<V; j++){
		cout <<  "INSIDE PRINT TSP" << endl;
		list<int>::const_iterator i;
		cout << "Size of " << j <<"->>> " << adj[j].size() << endl;	
	  	for(i = adj[j].begin(); i != adj[j].end(); ++i){
			cout << "Vertex: " << j << " Children: " << *i<< endl;
		}

	}
}

float tsp_15::calMean(){
	float mean = totaldistance;
	//mean = mean/(V);
	cout << "TSP 2 CALCULATED MEAN ~~~~~~~~~~~~~~~~~~~~~~ " << mean<< endl;
	return mean;


}
float tsp_15::calStd(){
	float std = 0.0;
	float mean = 0.0;

	mean = totaldistance/(V);
	
	while(!edgedistances.empty()){
			float stdpop = edgedistances.top();
			edgedistances.pop();
			std += (stdpop - mean)*(stdpop- mean);
	}
	
	std = sqrt(std/V);	

	cout << "TSP2 STANDARD DEVIATION ~~~~~~~~~~~~~> " << std << endl;
	return std;
	
}
	



