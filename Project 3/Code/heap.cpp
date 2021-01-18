/*
	This file defines the functions related to the min-heap and initializing the single souce.

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

void initializeSingleSource(minElement *minHeap, int sourceVertex, int numberOfVertices){
/*
	This function initializes the distance and predecessor vertices of each of the vertex
*/

	//Iterating over all the vertices starting from vertex '1'
	for(int i=1; i<numberOfVertices+1; i++){

		(minHeap+i)->vertex=i;						//	Marking the node for the vertex 
		(minHeap+i)->predecessorVertex= 0; 			//	Initializing the predecessor vertex to zero
		(minHeap+i)->knownMinimumDistance=10000;	//	Initializing the minimumknow distance to infinity
	} 	
	// cout<<"Source Vertex"<< sourceVertex<<endl;
	(minHeap+sourceVertex)->knownMinimumDistance=0;	// Setting the distance to self as zero.
}



void swap(minElement *minHeap, int smallest, int index){
/*
	This function swaps the smallest and the index element in the minHeap

*/	
	// int tempVertex = (minHeap+smallest)->vertex;									// Getting the vertex in the smallest node
	// int tempPredecessorVertex= (minHeap+smallest)->predecessorVertex; 				// Getting the pointer Pointer to the predecessor vertex in smallest node
	// int tempknownMinimumDistance = (minHeap+smallest)->knownMinimumDistance;		// Getting the knownMinimum Distance in the smallest node


	// /*
	// 	Copying the values from index to smallest;
	// */

	// (minHeap+smallest)->vertex = (minHeap+index)->vertex;						
	// (minHeap+smallest)->predecessorVertex = (minHeap+index)->predecessorVertex;
	// (minHeap+smallest)->knownMinimumDistance = (minHeap+index)->knownMinimumDistance; 


	// /*
	// 	Copying the values from smallest to index	
	// */



	// (minHeap+index)->vertex = tempVertex;						
	// (minHeap+index)->predecessorVertex = tempPredecessorVertex;
	// (minHeap+index)->knownMinimumDistance = tempknownMinimumDistance; 


	minElement temp= *(minHeap+smallest);
	*(minHeap+smallest)= *(minHeap+index);
	*(minHeap+index)= temp;
}






void minHeapify(minElement *minHeap, int index, int heapSize){
/*
	This function created a heap given the heap array and the index of the node/element in the array.
	
	-minHeap is the pointer to the minheap array
	-index is the position of the element where the minHeapify function is to be applied
	-heapSize is the size of the heap
*/

	int smallest;
	int left= 2*index;			//Getting the Left Sub Node index.
	int right=2*index + 1;		//Getting the Right sub node index.

	if (left <= heapSize && ((minHeap+left)->knownMinimumDistance) < (minHeap+index)->knownMinimumDistance){
		smallest=left;
	}

	else{
		smallest=index;
	}

	if (right <= heapSize && ((minHeap+right)->knownMinimumDistance) < (minHeap+smallest)->knownMinimumDistance){
		smallest=right;
	}

	if(smallest!=index){
		swap(minHeap, smallest, index);
		minHeapify(minHeap, smallest, heapSize);
	}

}


void createMinheap(minElement *minHeap, int heapSize){
/*

	This function creates the min-heap
*/


	//Looping over all elements except the leaf elements/nodes
	for(int i= heapSize/2; i>0; i--){
		minHeapify(minHeap, i, heapSize);
	}	

}

minElement extractminimumMinHeap(minElement *minHeap, int heapSize){
/*
	This function returns the minimum element in the minHeap
	
	-minHeap is the pointer to the minHeap
	-heapSize is the size of the heap

*/

	minElement minimumNode;		//	Variable to store the values of minimum node in the min-heap


	if(heapSize<1){
		cout<< "Heap underflow"<<endl; // Print error is heapsize is less than 1
	}

	/*
		Copying the required values	
	*/

	minimumNode.vertex= (minHeap+1)->vertex;
	minimumNode.predecessorVertex= (minHeap+1)->predecessorVertex;
	minimumNode.knownMinimumDistance= (minHeap+1)->knownMinimumDistance;

	/*
		Swap and call the minheapify function on the first element;
	*/


	swap(minHeap, 1, heapSize);	//	Swap the first element in the heap with the last element
	
	(minHeap+heapSize)->vertex=0;
	(minHeap+heapSize)->predecessorVertex=0;
	(minHeap+heapSize)->knownMinimumDistance=10000;

	heapSize--;
	minHeapify(minHeap, 1, heapSize);

	return minimumNode; 	//Return the minimum node

}


void minHeapInsert(minElement *S, minElement element, int heapSize){
/*
	This function inserts a new element in the min-heap

*/

	// If heapsize is zero
	if (heapSize==0){

		// Copying the necessary values

		(S+1)->vertex = element.vertex;
		(S+1)->predecessorVertex = element.predecessorVertex;
		(S+1)->knownMinimumDistance = element.knownMinimumDistance ;

	}


	else{
		heapSize++; //Increasing the heapsize

		int i= heapSize; // Setting a counter for the heapsize

		while (i>1 && ((S+parentNode(i))->knownMinimumDistance)>element.knownMinimumDistance){

			/*
				Passing the required values down the node
			*/


			(S+i)->vertex = (S+parentNode(i))->vertex;
			(S+i)->predecessorVertex = (S+parentNode(i))->predecessorVertex;
			(S+i)->knownMinimumDistance =(S+parentNode(i))->knownMinimumDistance;

			i=parentNode(i);
		}

		(S+i)->vertex = element.vertex;
		(S+i)->predecessorVertex = element.predecessorVertex;
		(S+i)->knownMinimumDistance = element.knownMinimumDistance ;
	}

}

int getOlddistance(minElement *minHeap, int vertex, int heapSize){
/*
	This function returns the current know minimum distance to the vertex from the source vertex
*/	

	//Looping over all the values in the minHeap
	for (int i=1; i<heapSize+1; i++){

		// Return the distance once we have found the vertex
		if((minHeap+i)->vertex == vertex){
			return (minHeap+i)-> knownMinimumDistance;
		}

	}

}

int updatePrecedenceVertexandDistance(minElement *minHeap, int vertex, int predecessorVertex, int newDistance, int heapSize){
/*
	This function updates the Precedence Vertex in the minHeap node
*/

	// If heapSize is only 1

	if( heapSize==1 ){

		(minHeap+1)->predecessorVertex = predecessorVertex ;
		(minHeap+1)->knownMinimumDistance = newDistance;

		return 1;
	}

	else{

		for(int i =1; i<heapSize+1; i++){
			if((minHeap+i)->vertex == vertex){
				(minHeap+i)->predecessorVertex = predecessorVertex ;
				(minHeap+i)->knownMinimumDistance = newDistance;
				return i;
			}
		}

	}
	

}

void heapDecreaseKey(minElement *minHeap, int index, int heapSize){
/*
	This function decreases the key of a node in the minHeap
*/


	int knownMinimumDistance = (minHeap+index)->knownMinimumDistance; 	// Getting the Key

	while(index>1 && ((minHeap+parentNode(index))->knownMinimumDistance)>knownMinimumDistance){
		// Swap the object values

		// cout<<index<<','<<parentNode(index)<<endl;
		
		// for (int i=1; i<heapSize+1; i++){
		// 	cout<< "Vertex: "<< (minHeap+i)->vertex<<','<< "Predecessor Vertex: "<< (minHeap+i)->predecessorVertex << ',' << "knownMinimumDistance: "<<  (minHeap+i)->knownMinimumDistance<<endl;
		// }
		// cout<<"---------------"<<endl;	
		
		swap(minHeap, parentNode(index), index);
		index= parentNode(index);
	}

}