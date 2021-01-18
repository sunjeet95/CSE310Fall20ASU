//JAI SHREE RAM //OM HUM HANUMATE NAMAH

/*
	This is the main file for project 3 in the CSE310:Fall2020 class.
	The project's main objective is to implement Dijkstra's Shortest Path Algorithm in directed graphs.

	Specificaally the entire code base does the followings:

	1) Build the adjacency list(linked list) for each vertex in the input(graph).
	2) Min-heap and min-heap priority list to store the distance of each vertex from the source 'S'.
	3) Calculating the shortest distance and path between a vertex (NOT Source) and Source.

*/


//Including the required libraries and header files

#include "heap.h"
#include "graph.h"
#include "utils.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;




int main(){

	int vertices, edges;						//	Variables to read number of vertices and number of edges.
	int startVertex, endVertex;					//	Variables to store the starting vertex and ending vertex of each edge.(Represents the Direction of the Edge!).
	float weightEdge;							//	Variable to store the weight of each edge. 

	string input;
	int data;									//	Variable to read the data of each vertex.
	string command; 							//	Variable to read the commands after the inputs to graphs have been read.


	adjacencyElement *adjacencyListElements;	//	Initializing a pointer adjacenyElement type.
	adjacencyElement **adjacencyList;			//	Initializing a pointer to the pointer to adjacenyElement type object. 	


	minElement *minHeap;						// Initializing the min-heap dynamic array for heap before the shortest path algorithm has been implemented.
	minElement *S;								// Initializing the min-heap dynamic array for heap after the shortest path algorithm has been implementd.	

	int dijkstraImplemented=0;					//Initializing a flag to verify if the shortest path to each vertex has been calculated or not.							


	cin>> vertices;								//	Reading the data that defines the number of vertices in the graph.
	cin>> edges;								//	Reading the data that defines the number of edges in the graph.	

	

	/*	

		Creating a dynamic array to store adjacencyElement type objects. 
	
	*/

	adjacencyListElements = new adjacencyElement[2*edges];

	/*	Creating a dynamic array to store pointers to adjacencyElements.
		The first element in the adjacencyList dynamic memory shall always be empty. Meaning --
		it shall store no adjacencyElement object because, our graph starts from vertex '1' and not '0'.
	*/
	adjacencyList = new adjacencyElement*[2*vertices];



	/*

		Creating a dynamic array, for min-heap.

		REMEMBER, in minHeap dynamic array the elements shall start from index 1 and NOT 0.

	*/

	minHeap= new minElement[vertices+2];
	S= new minElement[vertices+2];

	int readCounter=0; 			// This counter acts as a marker to which data we are currently reading. Resets to zero after reading the weight.
	int edgeCounter=0;			// Counter to count the number of edges which has been read. 
	while(cin>>input){

		if(input == "stop"){
			//If the Command read is stop
			cout<<"Command: stop"<<endl;
			return 0;
		}
		else if(input =="write"){
			//If command is 'write'

			cout<<"Command: write"<<endl;
			cout<<vertices<<" "<<edges<<endl; // Output the nmber of vertices and edges

			//Write all the adjacency vertices for EACH vertex.
			writeAdjacentVertices(adjacencyList, vertices);

		}

		else if(input == "find"){
			//If command is 'find s t _'
			int sourceVertex, finalVertex, flag; //Initializing the variables.

			cin>>sourceVertex;	//Reading the source vertex
			cin>>finalVertex;	//Reading the final vertex
			cin>>flag;   		//Reading the flag

			cout<<"Command: find "<< sourceVertex<<" "<<finalVertex<<" "<<flag<<endl; //Output the required data and command

			/*
				Check if the source vertex and the final vertex are valid nodes
			*/

			int checkSourceVertex = checkNode(sourceVertex, adjacencyList, vertices);
			int checkFinalVertex  = checkNode(finalVertex, adjacencyList, vertices);


			int vertexCheck=1; 	//	Vertex Check 		
			int flagCheck=1;	//	Flag Check


			if(checkSourceVertex ==0 || checkFinalVertex==0){
				cout<<"Error: one or more invalid nodes"<<endl;
				vertexCheck=0;
			}

			if((flag!=0) && (flag!=1)){
				cout<<"Error: invalid flag value"<<endl;
				flagCheck=0;
			}

			if(vertexCheck!=0 && flagCheck!=0){
			
				//If Dijkstra's algorithm has not been implemented.

				//Initialize-Single-Source
				initializeSingleSource(minHeap, sourceVertex, vertices);
				
				//Calling the funtion that implements the Dijkstra's algorithm	
				callDijkstrasAlgorithm(minHeap, S, adjacencyList, vertices);

				// for (int i=1; i<vertices+1; i++){
				// 	cout<< "Vertex: "<< (S+i)->vertex<<','<< "Predecessor Vertex: "<< (S+i)->predecessorVertex << ',' << "knownMinimumDistance: "<<  (S+i)->knownMinimumDistance<<endl;
				// }
				// while(1);

				if(flag==0){
					// Initializing an array to store all the vertices in the shortest past
					int vertexArray[vertices];

					//Reset the vertex array to clear any previous held values
					resetArray(vertexArray,vertices);

					//The function below adds All the vertices in the shortest path to the vertex array
					int pathExists=shortestPath(sourceVertex, finalVertex, S, vertexArray, vertices);


					//If a path exists
					if(pathExists){

						cout<<"Path: ";
						for (int i=0; i<vertices; i++){

							if(*(vertexArray+i)!=0){
								if(i!=vertices-1){
									cout<<*(vertexArray+i)<<';';
								}
								else{
									cout<<*(vertexArray+i);
								}
							}
						}
						cout<<endl;
					}	
					else{
						// If there exists no path
						cout<<"Error: node "<< finalVertex <<" not reachable from node "<< sourceVertex<<endl;
					}	

				}
				else if(flag==1){

					// The function below returns the length of the shortest path to the finalVertex array
					int length=shortestPathLength(finalVertex, S, vertices);
					
					if(length==10000){
						cout<<"Error: node "<< finalVertex <<" not reachable from node "<< sourceVertex<<endl;	
					}
					else{
						cout<<"Length: "<< length <<endl;
					}

				}	
			}
				 
		}
		else{
			
			data=stoi(input);					//Converting the read input into an integer.
			if(readCounter==0){
				//Counter to 0 means we read the start vertex of an edge.
				startVertex=data;
				readCounter++;					//Update the counter to indicate that the next input will the end vertex.
			}
			else if(readCounter==1){
				//Counter to 1 means we read the end vertex of an edge.
				endVertex=data;
				readCounter++; 					//Update the counter to indicate that the next input will the weight of the edge.
			}
			else if(readCounter==2){
				//Counter to 2 means we read the weight of the edge.
				weightEdge=data;
				readCounter=0;					// Reset the counter to indicate that the next input will the start vertex of a new edge
				
				/*
					Creating an object to store the read edge.
					All the edges are stored in an array.
					They are connected via a linked list (adjacent vertices), in the adjacencyList array. 
				*/
				(adjacencyListElements+edgeCounter)->rootVertex=startVertex;
				(adjacencyListElements+edgeCounter)->adjacentVertex= endVertex;
				(adjacencyListElements+edgeCounter)->distanceVertex= weightEdge;

				//Inserting the adjacencyListElement into the adjacency list
				insert_to_adjacencyList(adjacencyListElements+edgeCounter, adjacencyList, startVertex, endVertex, weightEdge);

				edgeCounter++;				//Updating the edge counter

			}
		}
	}


	delete [] adjacencyListElements;
	delete [] adjacencyList;
	delete [] minHeap;
	delete [] S;
}



