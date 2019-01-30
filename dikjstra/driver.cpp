/*
 * Driver.cpp
 *
 *  Created on: May 5, 2016
 *      Author: inson
 */

// g++ driver.cpp -o driver.out
// ./driver.out

#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]){

	ifstream inputFile;

	inputFile.open(argv[1]);



	Graph* gr = new Graph(argv[1]);
	gr->dikjstraPath();




	cout  << "End of the program!!" <<  endl;

	//cout << (2 << 2) << endl;

	delete gr;

	return 0;

}
