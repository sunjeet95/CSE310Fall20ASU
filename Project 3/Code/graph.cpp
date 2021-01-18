/*
	This file defines the functions related to the graph and adjacency list.

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


void insert_to_adjacencyList(adjacencyElement *adjacencyListElements, adjacencyElement **adjacencyList, int startVertex, int endVertex, int weightEdge){
/*	This functions inserts the vertex in the adjacency list.
	
	- adjacencyListElements is the pointer/array to store the objects of the adjacencyElement type objects
	- adjacencyList is the pointer/array to/of pointers' to store the adjacency linked list.
	- startVertex is the vertex of whose adjacent element we shall be storing.
	- endVertex is the adjacent vertex.
	- weightEdge is the weight of the edge to the adjacent vertex.

	Remember, the first element in the adjacencyList dynamic memory shall always be empty. Meaning --
	it shall store no adjacencyElement object because, our graph starts from vertex '1' and not '0'.

*/	

	//Base Case. Where we haven't found an adjacent vertex to a particalur vertex yet.
	if(*(adjacencyList + startVertex) == 0){
		*(adjacencyList + startVertex)=adjacencyListElements;
	}

	else{
		//If adjacent elements already exists


		/*
			Implementing seperate chaining, to create a linked list.
			First link the newly created element to the previously read adjacent vertices(elements?),
			then link the pointer stored in the adjacenyList array to the new element/ adjacent vertex. 
		*/
		adjacencyListElements->NextVertexinLinkedList= *(adjacencyList + startVertex);
		*(adjacencyList + startVertex)=adjacencyListElements;
	}

}


void writeAdjacentVertices(adjacencyElement **adjacencyList, int vertices){
/*	This functions outputs all the elements in the adjacency list. 
	
	- adjacencyListElements is the pointer/array to store the objects of the adjacencyElement type objects.
	- vertices is the total number of vertices in the graph.

	Remember, the first element in the adjacencyList dynamic memory shall always be empty. Meaning --
	it shall store no adjacencyElement object because, our graph starts from vertex '1' and not '0'.

*/
	//Starting loop to output adjacent vertices of EACH vertex
	for(int i=1; i<vertices+1; i++){

		//Create a pointer variable to go through the linked list.
		adjacencyElement *adjacentVertexPtr= *(adjacencyList + i);

		cout<<i<<" : ";

		//Loop until the last element in the linked list.
		while(adjacentVertexPtr!=0){
			cout<<"("<<adjacentVertexPtr->adjacentVertex<<"; "<<adjacentVertexPtr->distanceVertex<<")"; //Output the adjacent vertex and the weight of the edge to the vertex
			adjacentVertexPtr=adjacentVertexPtr->NextVertexinLinkedList;	//Moving to the next adjacent vertex
			if(adjacentVertexPtr!=0){
				//Using semi-colon deliminater only when the next vertex exists.
				cout<<"; ";
			}
		}
		cout<<'\n';
	}
}



void callDijkstrasAlgorithm(minElement *minHeap, minElement *S, adjacencyElement **adjacencyList, int heapSize){
/*
	This function implements the Dijkstra's Shorted Path Algotihtm

	- minHeap is pointer to the array that implements the min heap BEFORE the shortest path algorithm has been implemented
	- S is pointer to the array that implements the min heap AFTER the shortest path algorithm has been implemented.
	- adjacencyList is an array(pointer to pointer?) of elements which implements adjacency linked list.
	- heapSize is the size of the heap
	
*/
	createMinheap(minHeap, heapSize);				//	This function creates the minheap on the 'minheap' array/pointer BEFORE the dijkstra's algorithm is implemented.
	int heapSizeofS=0;								// Initialzing the heapsize of S


	/*
		We iterate until the heap is zero!
	*/

	int c=0;
	while(heapSize!=0){
		c++;

		minElement newMinimum= extractminimumMinHeap(minHeap, heapSize);		//	Getting the vertex with minimum distance
		heapSize--;																//	Decrease the Heap Size
		minHeapInsert(S, newMinimum, heapSizeofS);								//  Insert the element into the 'S' array/heapsort
		heapSizeofS++;															//  Increase the size of the 'S' array

		int selectedVertex = newMinimum.vertex;									// Getting the selected vertex
		int distanceofVertexfromSource = newMinimum.knownMinimumDistance; 		// Distance of the selected vertex from source
		// cout<<selectedVertex<<','<<distanceofVertexfromSource<<endl;
		adjacencyElement *adjacentVertexPtr=*(adjacencyList+selectedVertex);	//Initializing the adjacentVertexPtr to loop over all adjacent vertices


		/*
			Looping over all the adjacent elements using the linked list
		*/		

		// for (int i=1; i<heapSize+1; i++){
		// 			cout<< "Vertex: "<< (S+i)->vertex<<','<< "Predecessor Vertex: "<< (S+i)->predecessorVertex << ',' << "knownMinimumDistance: "<<  (S+i)->knownMinimumDistance<<endl;
		// 		}
		// 		while(1);

		while(adjacentVertexPtr!=0){

			// Getting the necessary variables



			if((adjacentVertexPtr)->adjacentVertex!=selectedVertex){
				int adjacentVertex= adjacentVertexPtr->adjacentVertex;
				int distanceofadjacentVertexfromSelected=adjacentVertexPtr->distanceVertex;
				
				int oldDistanceofAdjacentVertexfromSource = getOlddistance(minHeap, adjacentVertex, heapSize); // Getting the old known minimum distance		

				/*
					The Code below implements the relax function on the edge to the current adjacent vertex

				*/
				if( oldDistanceofAdjacentVertexfromSource > distanceofadjacentVertexfromSelected + distanceofVertexfromSource){

					// Update the precedence vertex and the new known minimum distance
					// Returns its index position in the min heap
					int updatedVertexIndex= updatePrecedenceVertexandDistance(minHeap, adjacentVertex, selectedVertex, distanceofadjacentVertexfromSelected + distanceofVertexfromSource, heapSize);
					
					// Now we implement the DECREASE-KEY Priority function on minHeap
					// NOTE: We have already decreased the key using te updatePrecedenceVertexandDistance Function. We are only restructuring the heap in the below function,
					// that is why we don't need the key and only the index position

					heapDecreaseKey(minHeap, updatedVertexIndex, heapSize);
				}

			}

			// Going to the next object in the linked list'c
			adjacentVertexPtr=adjacentVertexPtr->NextVertexinLinkedList;
		}

	}

}

int shortestPath(int sourceVertex,int finalVertex, minElement *S, int *vertexArray, int maxVertices){
/*
	This function puts all the vertices in the shortest path to the finalVertex
*/	

	// If Source Vertex is same as final vertex
	if(sourceVertex==finalVertex){

		addElementtoArray(vertexArray, finalVertex, maxVertices);
		return 1;
	}

	else{
		for(int i=1; i<maxVertices+1; i++){

			if((S+i)->vertex==finalVertex){
				
				// Add the vertex to the array
				addElementtoArray(vertexArray, finalVertex,maxVertices);

				finalVertex= (S+i)->predecessorVertex;
				//Reset i counter
				i=1;
			}

			//Once we have reached to the starting point of the shortest path break the loop
			if(finalVertex==sourceVertex){
				addElementtoArray(vertexArray, sourceVertex,maxVertices);
				return 1;
			}
		}
		return 0;
	}
}

int shortestPathLength(int finalVertex, minElement *S, int maxVertices){
/*
	This function return the length of the shortest path
*/

	for(int i=1; i<maxVertices+1; i++){

		if((S+i)->vertex==finalVertex){
			return (S+i)->knownMinimumDistance;
		}

	}
}