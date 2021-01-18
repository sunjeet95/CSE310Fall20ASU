/*
	This header file defines the structure of each element of the adjacency list (linked list)
								AND
	declares all function declaration related to the graph and adjacency list.
*/


#ifndef GRAPH_H
#define GRAPH_H

//Including the required libraries and header files
#include "heap.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;

struct adjacencyElement
{	
	int rootVertex=0;							//	Variable to store the root vertex of the adjacent vertex
	int adjacentVertex;							//	Variable that stores adjacent vertex (adjacent vertex name?)
	int distanceVertex;							//	Distance of the vertex from the root vertex (Root is NOT Source!!!) // Root Specifically mean the vertex under consideration 
	adjacencyElement *NextVertexinLinkedList;	//	Pointer to design a linked list to design a chain of all adjacent vertices to a root vertex (Root is NOT Source!!!) // Root Specifically mean the vertex under consideration 
};




void insert_to_adjacencyList(adjacencyElement *adjacencyListElements, adjacencyElement **adjacencyList, int startVertex, int endVertex, int weightEdge);
void writeAdjacentVertices(adjacencyElement **adjacencyList, int vertices);
void callDijkstrasAlgorithm(minElement *minHeap, minElement *S, adjacencyElement **adjacencyList, int heapSize);
int shortestPath(int sourceVertex,int finalVertex, minElement *S, int *vertexArray, int maxVertices);
int shortestPathLength(int finalVertex, minElement *S, int maxVertices);

#endif