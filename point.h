#include "common.h"
#include <map>
#include <stack>

#pragma once

class Point{ 
//using namespace std;
public:
	int** adjacentMatrix;
	int pointNum; //the number of generated pointset
	set< pair<int,int> > pointset;
//	multimap<int, int> multi;
//	multimal<int,int>::iterator it;
//	stack<int> mystack;

	Point();
	~Point();

	void generatePoint(unsigned int H, unsigned int W, unsigned int N);
	set< pair<int,int> > getPointset();
	void setPointset();
	int ** getAdjacentMatrix();
	int getPointNum();
	void printPointset();

private:
	int getEuclideanDistance(int x1, int y1, int x2, int y2);
};
