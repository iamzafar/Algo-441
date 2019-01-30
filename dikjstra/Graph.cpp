/*
 * Graph.cpp
 *
 *  Created on: May 7, 2016
 *      Author: inson
 */

#include "Graph.h"

Graph::Graph(char* file):maxNode(0) {

	cout << "Inside of the Graph\n";

	string str;

	input.open(file);
	if(input.fail()){
		cout << "Cannot open the file " << file << endl;
	}



	// printing the nodes
	/*while(!input.eof()){

			getline(input, str);
			cout << str << endl ;
	}*/

	//pair<int, int> vertex;

	//vertex = make_pair(1, 2);

	//cout << "pair " << vertex.first << endl;



	createAdjMatrix();


}

// =========================================================================
void Graph::dikjstraPath(){

	cout << "Inside of the dikjstra path!!!\n";
	int dist[maxNode];

	 bool sptSet[maxNode];

	 // Parent array to store shortest path tree
	 //int parent[maxNode];


	 // Initialize all distances as INFINITE and stpSet[] as false
	 for (int i = 1; i <= maxNode; i++)
	 {
		// parent[0] = -1;
		 dist[i] = INT_MAX;
		 sptSet[i] = false;
	 }

	 // Distance of source vertex from itself is always 0
	 dist[source] = 0;

	 for(int i = 1; i <= maxNode; i++){

		 cout << "Inside of the for loop for getting mindistance\n";
		 // Pick the minimum distance vertex from the set of
		 // vertices not yet processed. u is always equal to src
		 // in first iteration.
		 int u = getMinDistance(dist, sptSet);

		 // Mark the picked vertex as processed
		 sptSet[u] = true;

		 for (int v = 1; v <= maxNode; v++){

			 // Update dist[v] only if is not in sptSet, there is an edge from
			 // u to v, and total weight of path from src to  v through u is
			 // smaller than current value of dist[v]


			 if ((!sptSet[v] && matrix[u -1][v -1]) && (dist[u] != INT_MAX)
					 && (dist[u]+matrix[u -1][v -1] < dist[v]))
				 dist[v] = dist[u] + matrix[u -1][v -1];}

	 }

	 printPath(dist);

}


// creating table
void Graph::createAdjMatrix(){

	string str;
	string line = "";
	int num = 0;
	vector<int> nodes;

	vector<int> singleRow;
	vector< vector<int> > verteces;


	while(!input.eof())
	{
				int nodeNum = 0;
				getline(input, str);
				if(str != ""){
					// check if there is Source and destionation nodes
					if((str.at(0) >= 'a' && str.at(0) <= 'z') || (str.at(0) >= 'A' && str.at(0) <= 'Z'))
					{


						// check if source is found
						if(str.substr(0, 6) == "Source" || str.substr(0, 6) == "source"){
							int position = str.find("$");
							//cout << str.substr(position+1) << endl;
							cout << "Source is >>> " << str.substr(position+1) << endl;
							setSource(atoi(str.substr(position+1).c_str())); // source
						}else{
							int position = str.find("$");
							cout << "destination  is >>> " << str.substr(position+1) << endl;
							setDestination(atoi(str.substr(position+1).c_str())); // destination
						}
					}else{ // read vertices and weight between adjacent vertices
						istringstream iss(str);
						while(getline(iss, line, '$')){
							singleRow.push_back(atoi(line.c_str()));

							if(nodeNum < 2){
								nodes.push_back(atoi(line.c_str()));
							}

							//cout << line << " ";
							num = atoi(line.c_str());
							cout << num << " ";
							nodeNum++;
						}
						verteces.push_back(singleRow); // making 2D array
						singleRow.clear(); // clearing single row

					}
				}
				cout << endl;


	}

	//cout << "SIZE of the array nodes " << nodes.size() << endl;

	maxNode  = getMaxNode(verteces);
	cout << "Max node is " << maxNode << endl;

	createMatrix(getMaxNode(verteces), verteces);

	//dikjstraPath();
}


// find the max node
// define the size of the array from the max node

int Graph::getMaxNode(std::vector< vector<int> > nodes){

	int max = -1;
	if(nodes.size() == 0){
		cout << "Vector of verteces is empty!" << endl;
		exit(0);
	}else{
		max = nodes[0][0];
		for(unsigned int i = 0; i < nodes.size(); i++){
			for(unsigned int j = 0; j < nodes[i].size() - 1; j++){
				if(nodes[i][j] > max)
					max = nodes[i][j];
			}
		}
	}
	//maxNode = max;
	return max;
}

//-------------------------------------------------------------------------------
// creating actual matrix of nodes
void Graph::createMatrix(int maxVertex, vector< vector<int> > map){

	cout << "Insied of creating a matrix!!!\n";
	//int verteces[maxVertex][maxVertex];
	// fill the array with -1
	/*for(int i = 0; i < maxVertex; i++){
		for(int j = 0; j < maxVertex; j++){
			verteces[i][j] = -1;
		}
	}
	cout << verteces[1][2] << endl;*/

	// populating the map with -1 distances
	int count = maxVertex;
	while(count > 0){
		vector<int> row(maxVertex, 0);
		matrix.push_back(row);
		row.clear();
		count--;
	}

	// populating matrix with actual distances
	for(unsigned int i = 0; i < map.size(); i++){
		// get the edge
		int x = map[i][0] - 1;
		int y = map[i][1] - 1;

		// connect edges with distance
		matrix[x][y] = map[i][2];
		matrix[y][x] = map[i][2];
	}

	// printing the array
	cout << "ARRAY!\n";

	cout << "   1   2   3   4   5   6" << endl;
	cout << "------------------------" << endl;
	for(unsigned int j = 0; j < matrix.size(); j++){

		cout << j +1 << "| ";
		for(unsigned int k = 0; k < matrix[j].size(); k++){
			cout <<  matrix[k][j] << "   ";
		}
		cout << endl;
	}

}

/*
 * Setting destination and source
 */

void Graph::setDestination(int y){
	destination = y;
}

void Graph::setSource(int x){
	source = x;
}

// printing the path
void Graph::printPath(int dist[]){
	cout << "Vertex   Distance from Source" << endl;
	for (int i = 1; i <= maxNode; i++)
		//  printf("%d \t\t %d\n", i, dist[i]);
		cout << i << "\t\t" << dist[i] << endl;
}

// finding minimum distance between verteces
int Graph::getMinDistance(int dist[], bool verteces[]){
	// Initialize min value
	cout << "Inside of get MIN distance ------\n";

	int min = INT_MAX, min_index;

	for (int i = 0; i < maxNode; i++){
		if (verteces[i] == false && dist[i] <= min)
			min = dist[i], min_index = i;
	}

	cout << "returning MIN index " << min_index << endl;
	return min_index;
}

// last node is returning different value



