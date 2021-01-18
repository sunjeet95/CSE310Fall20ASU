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


int main(int argc, char *argv[]){

	string line, *str_ptr;
	int clustered_=0;
	string *Str_Array=NULL;
	while(getline(cin, line)){
		if(line.size()!=0){
			Str_Array= new string[line.size()];//Creating a dynamic memory to Store the Cyclic Shifted Strings/Lines
			string key; // Key is the most recent cyclic shifted string/line. Starts with the original line itself

			int len_=line.size();// Getting the length of the string/line

			//Transformation function
			for(int i=0; i<len_; i++){ 	//Iterating over the length of the string/line


				if(i==0){
					key=line; //Setting the original line/string as key
					Str_Array[i]=key; //Original string/line is stored in the 0th index of the array	
				}
				else{
					key=cyclic_function(key,1); //Getting the cyclic shifted string/line and updating the key
					Str_Array[i]=key; //Storing the the updated key in the array
				}
			}

			if(argv[1][0]=='i'){		
				str_ptr=insertion_sort(Str_Array,len_); //Calling the insertion sort function and getting the pointer to the first element
																//in sorted array
			}
			else{
				string *p= Str_Array;
				string *r= Str_Array + len_-1;
				str_ptr=quicksort(Str_Array, p, r);			
			}

			// auto rd_ptr=str_ptr;
			// while(rd_ptr!=Str_Array+len_){
			// 	cout<<(*rd_ptr)<<endl;
			// 	rd_ptr++;
			// }
			// cout<<"-----END-----"<<endl;


			/*Calling the binary search function to get the index of the Original line in the sorted array
			  Return an unsigned int
			*/
			unsigned int index=binary_search(line, str_ptr, len_);
			cout<<index<<endl;
			
			//Calling the cluster funtion //Function directly streams the output to file
			
			clustered_=cluster(str_ptr, len_);
			
			delete [] Str_Array; //Deleting the dynamic memory
		}
		else{
			//For line with no characters
			cout<<'\n';
		}
	}
}