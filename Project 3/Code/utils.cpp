/*
	This file contains all the utility functions related to Project 3.
*/

//Including the required libraries and header files


#include "utils.h"
#include "heap.h"
#include "graph.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;


int checkNode(int vertex, adjacencyElement **adjacencyList, int vertices){
/*
	This function vertifies if the vertex exists or not in the graph.
*/

	int counter=1;

	// Looping over every vertex to check
	while(counter < vertices+1){

		// Checking if the pointer points to something
		if((*(adjacencyList+counter))!=0){
			if((*(adjacencyList+counter))->rootVertex == vertex){
				return 1;
			}
		}	
		counter++;
	}
	return 0;
}

int parentNode(int index){
/*
	This Function returns the parent of the index;
*/

	return index/2;

}

void resetArray(int *vertexArray, int vertices){
/*
	This function resets an array to all zero
*/

	for(int i=0;i<vertices;i++){
		*(vertexArray+i)=0;
	}

}

void addElementtoArray(int *vertexArray, int vertex, int maxVertices){
/*
	This function adds an element to the array
*/	
	

	int i=maxVertices-1;	//Initializing a reverse counter

	//Finding the first zero/blank space
	while(*(vertexArray+i)!=0 && i>0){
		i--;
	}

	//Adding the element to the array
	*(vertexArray+i)=vertex;
}