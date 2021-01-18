/*
	This header file declares all functions related to the utils.cpp.
*/


#ifndef UTILS
#define UTILS

//Including the required libraries and header files
#include "heap.h"
#include "graph.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;


int checkNode(int vertex, adjacencyElement **adjacencyList, int vertices);
int parentNode(int index);
void resetArray(int *vertexArray, int vertices);
void addElementtoArray(int *vertexArray, int finalVertex, int maxVertices);

#endif