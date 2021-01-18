/*
	This header file defines the structure of each element of the min heap sort
								AND
	declares all function declaration related to the heap function.
*/

#include "graph.h"
#ifndef HEAP_H
#define HEAP_H

//Including the required libraries and header files

#include <iostream>
#include <string>

struct minElement
{

	int vertex=0;					//Vertex in the graph
	int predecessorVertex=0; 	//Pointer to the predecessor vertex
	int knownMinimumDistance=0; 	//Current known minimum Distance
};


//Declaring the functions related to the heap.
void initializeSingleSource(minElement *minHeap, int sourceVertex, int numberOfVertices);
void createMinheap(minElement *minHeap, int heapSize);
minElement extractminimumMinHeap(minElement *minHeap, int heapSize);
void minHeapInsert(minElement *S, minElement element, int heapSize);
int getOlddistance(minElement *minHeap, int vertex, int heapSize);
int updatePrecedenceVertexandDistance(minElement *minHeap, int vertex, int predecessorVertex, int newDistance, int heapSize);
void heapDecreaseKey(minElement *minHeap, int index, int heapSize);
#endif