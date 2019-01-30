/*
 * Graph.h
 *
 *  Created on: May 7, 2016
 *      Author: inson
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;


class Graph {
public:
	Graph(char* file);
	void dikjstraPath();

private:
	ifstream input;
	void createAdjMatrix();
	bool isAdjacent(std::string edge);
	int getMaxNode(std::vector< std::vector<int> > nodes);
	void createMatrix(int maxVertex, std::vector< vector<int> > map);
	void setDestination(int y);
	void setSource(int x);
	int getMinDistance(int dist[], bool verteces[]);
	void printPath(int dist[]);








	//vector<int> nodes;
	//vector<vector<int> > verteces;
	int destination;
	int source;
	int maxNode;
	vector< vector<int> > matrix;


};

#endif /* GRAPH_H_ */
