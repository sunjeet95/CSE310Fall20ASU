//Jai Shri Ram //Om Hum Hanumate Namah //

//Including the required libraries
#include <iostream>
#include <string>
#include "project_header.h"

//Including the required classes from std namespace
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;

int main(int argc, char *argv[]){

	/*Initializing the required variables
	  StringArray will be used to store the UNSORTED decoded cluster characters
	  SortedStringArray will be used to store the SORTED decoded cluster characters	
	*/

	string line, *str_ptr1;
	string *StringArray=NULL;
	string *SortedStringArray=NULL;
	int index=0;
	int decode;

	/*The Below markers are used to to detect what the getline is reading
	  indexMarker=1 means the the line shall be the index of the original line in the sorted array
	  encodingMarker=1 means the next line shall be the line encodings	
	  We start with indexMarker=1 and encodingMarker=0 as at the beginning of the file the first non-white line will be the index value	
	*/ 
	int indexMarker=1;
	int encodingMarker=0;

	// Calling the getline in a while loop. Runs until we reach the end of the loop
	while(getline(cin, line)){

		//Verifying if the line is empty or not
		if(line.size()!=0){
			//Verifying if the current line read is an Index value
			if(indexMarker==1){
				//Coverting the string into an integer
				index=stoi(line);

				//Resetting the indexMarker=0 and setting encodingMarker=1 as the next line will be an encoding
				encodingMarker=1;
				indexMarker=0;
			}
			//Verifying if the current line read are encodings
			else if(encodingMarker==1){
				//Initializing the required variables
				int totalLengthLine=0;
				string temp;
				string temp2;
				string temp3;
				string temp_char;

				//This loop shall calculate the total line length by summing over all the cluster sizes
				for(int i=0; i<line.size(); i++){
					/*As the characters are read sequentially, we need to keep appending the numbers 
					  unitl we reach a white space
					*/
					temp=line[i];
					if(temp!=" "){
						//Concatenating the character number
						temp2=temp2+temp;

					}
					/* Once we hit a white space, we know the result of previous concatenation will be the cluster size of a character*/
					else{
						//Converting that number and adding to the totalLengthLine
						totalLengthLine=totalLengthLine+stoi(temp2);
						//Resetting the temp2 variable for next value
						temp2="";

						//This condition is used to jump over the character which was cluster
						if(i+2<=line.size()){
							i=i+2;
						}
					}
				}

				//Creating two dynamic size memory
				StringArray = new string [totalLengthLine];
				SortedStringArray = new string [totalLengthLine];

				//Below is NOT a C++ pointer. It has just been used to point the next position free position in the StringArray and SortedStringArray 
				int pointerFree=0;

				/*This loop will unwind all the encodings in a line sequentially and store them in both StringArray memory and SortedStringArray Memory*/
				for(string::size_type i=0; i<line.size(); i++){
					temp=line[i];
					
					//Until we hit a white space, all the character integers read till that point concatenates to denote one number
					if(temp!=" "){
						temp3=temp3+temp;
					}

					else{
						/*Once we hit the white space, we know the cluster size and also that the next character in the line sequence is the cluster character*/

						int clusterSize= stoi(temp3);
						temp_char=line[i+1];
						string cluster=temp_char;
						temp3="";
						//Looping over till clusterSize>0
						while(clusterSize>0){
							StringArray[pointerFree]=cluster;
							SortedStringArray[pointerFree]=cluster;
							//Updating the required counters
							clusterSize--;
							pointerFree++;
						}
						//This condition is used to jump over the character which was cluster
						if(i+2<=line.size()){
							i=i+2;
						}
					}
				
				}
				//Sorting the characters using insertion sort
				if(argv[1][0]=='i'){		
				SortedStringArray=insertion_sort(SortedStringArray,totalLengthLine); //Calling the insertion sort function and getting the pointer to the first element
																		  //in sorted array
				}
				//Sorting the characters using quicksort
				else{
					string *p= SortedStringArray;
					string *r= SortedStringArray + totalLengthLine-1;
					SortedStringArray=quicksort(SortedStringArray, p, r);				
				}


				decode=decode_function(StringArray, SortedStringArray, index, totalLengthLine);

				delete [] StringArray;
				delete [] SortedStringArray;

				encodingMarker=0;
				indexMarker=1;
			}
		}
		//If the line is empty we just print the line('\n')
		else{
			cout<<line<<endl;
		}
	}

}