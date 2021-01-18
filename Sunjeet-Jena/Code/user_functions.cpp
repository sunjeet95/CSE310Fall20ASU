#include <iostream>
#include <string>
#include "project_header.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;



string& cyclic_function(string& test_line, int shift){
//This is the cyclic shift function, which shifts characters to the left
//It takes two variables, test_line is a reference to the string and shift is the number of characters we looking to shift. 
//Note currently it supports only 1 character shift to left
	//Getting the first character in the string
	char key=test_line[0];
	//Shifting each character to the left except the first character
	for(auto i_ptr=test_line.begin(); i_ptr!=test_line.end(); i_ptr=i_ptr+shift){

		*i_ptr=*(i_ptr+1);
	}
	//Finally we put the first character in the last position of the string
	test_line[test_line.size()-1]=key;
	//Return the reference to the shifted string
	return test_line;
}

string* insertion_sort(string *array_, string::size_type len){
//Input to the function are an array of string (Pointer to the first element in the array) and length of the line
//The function returns a pointer to the first element of the sorted array.
	if(len==1){
		//If the string length is 1, its already sorted
		return array_; //Returning the pointer to the element. Note array_ here means the pointer to the element.
	}
	else{
		
		string *i_ptr=array_; //Pointer to the first element in the array
		for(auto c_ptr=array_+1; c_ptr!=array_+len;c_ptr++){			
		string key= *c_ptr;
			
			//Comparing the key with the previous sorted array
			while(c_ptr!=i_ptr && *(c_ptr-1)>(key)){

				//Shifting the greater element to the right
				*c_ptr=*(c_ptr-1);

				//Updating the counter pointer		
				c_ptr=c_ptr-1;
			}

			//Storing the key in the right index
			*c_ptr= key;
	
		}

	}
	return array_; //Returning the pointer to the element. Note array_ here means the pointer to the element.
}



int cluster(string *array_, int len_){
// The input to the function are the sorted array(Pointer to the first string in the sorted array) and length of the string
// Return a 0 on successful completion of the function
// NOTE:The function directly streams the clusters to the output file	
	

	int ctr; //Defining the counter to count the continuous repetition characters
	char key; //Key is the current character cluster


	//Iterating for all the strings
	for(string *i_ptr=array_; i_ptr!=array_+len_;i_ptr++){
		
		//For first string, the ctr==1 and key is last character of the string
		if(i_ptr==array_){
			ctr=1;
			key= (*i_ptr)[len_-1];
		}
		else{
			//Checking if the end character of the current string matches with the current key
			if((*i_ptr)[len_-1]==key){
				ctr++;
			}
			else{
				//If the end character of the current string DOESNT match with the current key 
				//Stream the Ctr(count) and key(char) to the output file
				
				cout<<ctr<<' ';
				cout<<key<<' ';
				//Reset the ctr to one and key to the last element of the current string
				ctr=1;
				key=(*i_ptr)[len_-1];
			}
		}
	}
	//Stream the last Ctr(count) and key(char) to the output file
	cout<<ctr<<' ';
	//cout<<key<<' '<<endl;
	cout<<key<<endl;
	return 0;

}

unsigned int binary_search(string& line, string *array_, int len_){
//The function does a binary search to find the index of the original line in the sorted array
// The input to the function are the original line, the sorted array(Pointer to the first string in the sorted array) and length of the string
//Returns the index position of the original string in the sorted array

	if(*array_==line){
		//Return 0 if found in the first index
		return 0;
	}
	else{
		//Getting the pointer to the first element
		string *b_ptr=array_;
		//Getting the pointer to the last element
		string *e_ptr=array_ + len_;
		//Getting the pointer to the middle element
		string *m_ptr=b_ptr + (e_ptr - b_ptr)/2;	

		//We check until we reach the end of the array or middle pointer matches the required element
		while(m_ptr!=e_ptr && *m_ptr!=line){
			if(*m_ptr>line){
				e_ptr=m_ptr;
			}
			else{
				b_ptr=m_ptr+1;
			}
			m_ptr=b_ptr + (e_ptr - b_ptr)/2;
		}
		//Returning the index of the required array
		return (m_ptr-array_);
	}

}


bool checkAvailability(int *NotAvailablePtr, int index, int totalLengthLine){
/* This function checks if a particular character has already been taken or not and returns True or False
   It takes 3 variables. NotAvailablePtr is the pointer to the elements in the NotAvailablePtr dynamic memory which keeps a track of what index positions have been taken.
   index is the index position of whose availability we are checking for.
   totalLengthLine is the total length of the line we are decoding OR the total number of characters in a line.

*/	
	//We iterate over the entire dynamic memory and compare index to each of it elements
	for(int i=0; i<totalLengthLine; i++){

		//If it exists in the NotAvailablePtr dynamic array we return false
		if(*(NotAvailablePtr+i)== index){
			return 0;
		}
	}
	//Not such index exists then we return True.
	return 1;
}

int	matchingFunc(string *StringArray, string *SortedStringArray, string rightChar, int *NotAvailablePtr, int indexcurrentShifted, int totalLengthLine){
/*This is the matching function.
  The matchingFunc, and we check which matching character to the second character of currentShifted is available and return its index position.
  It takes 6 variables. 
*/  
	//We iterate of the entire length of the line to find the available matching character
	for(int counter=0; counter<totalLengthLine; counter++){
		//Condition to make sure it doesn't match with itself
		if (counter!=indexcurrentShifted){

			//Getting a character from the StringArray memory
			string matchingChar=*(StringArray+counter);
			if(rightChar==matchingChar){
				//If it matches we check if its available or not
				bool available= checkAvailability(NotAvailablePtr, counter, totalLengthLine);

				if(available){
					*(NotAvailablePtr+indexcurrentShifted)=counter;
					return counter;
				}
			}

		}
	}	
	return 0;
}

int decode_function(string *StringArray,string *SortedStringArray, int indexPosition, int totalLengthLine){
/* This tis the decoding function. It taken 4 arguments. 
   StringArray is the pointer to unsorted array which we get after expanding the cluster
   SortedString Array is the pointer to the sorted version of the StringArray
   indexPosition is the index postion of the original line in sorted order of cyclic shifted characters in the encoded function.
   totalLength is thr true length of the line we can decoding
*/
	
	//Intialzing two pointers to integers
	//NotAvailablePtr keeps a note which position have been taken
	//Next keeps a track of the index position character is to be read next
	int *NotAvailablePtr;
	int *next;

	//Initializing two dynamic memory
	NotAvailablePtr= new int[totalLengthLine];
	next= new int[totalLengthLine];

	//We fill the NotAvailable dynamic memory with -1 as we know that the index values will never be -1
	int temp=0;
	while(temp<totalLengthLine){
		*(NotAvailablePtr+temp)= -1;
		temp++;
	}

	//Iterating over the total lenth of the line i.e. the number of characters
	for(int counter=0; counter<totalLengthLine; counter++){
		//We first get the string which we shall get after shifting the characters to the left 
		string currentShifted= *(StringArray+counter) + *(SortedStringArray+counter);
		//We call the matchingFunc, and we check which matching character to the second character of currentShifted is available and return its index position 
		*(next+counter)=matchingFunc(StringArray, SortedStringArray, *(SortedStringArray+counter), NotAvailablePtr, counter, totalLengthLine);
	}


	//Printing out the character one at a time using the next dynamic memory
	while(totalLengthLine>0){
		cout<<*(SortedStringArray+indexPosition);
		indexPosition=*(next+indexPosition);
		totalLengthLine--;
	}


	cout<<'\n';

	delete [] NotAvailablePtr;
	delete [] next;
	return 0;
}



/*All the functions below are part of the Quick Sort algorithm */


void swap_function(string* A, string* B){
//Swap function to swap strings between two pointers
	string temp= *A;
	*A = *B;
	*B = temp; 

}

string* partition_(string* P, string* R){
//Partition function to partition the array in two halves and return the Pivot position
// The functions takes two arguments: One is pointer to the first string in the array and the other is pointer to the last element in the array
	
	//If both the pointers point to the same element return one of the pointers
	if(P==R){
		return R;
	}

	//If the difference is only i.e. they are successive pointers
	else if( (R-P) == 1){
		//If *P is greater than *R swap P and R and return P or else return R
		if(*P>*R){
			swap_function(P, R);
		    return P;
		}
		
		else{
			return R;
		}
	}

	else{

		string* i=P; //Start the i pointer from the start of the array
		string* j=R-1; //Last element is the pivot element thus we initialize j from one position less than the last element
		
		//Loop until i is less than j and i<R and j>=P
		while(i<j && i<R && j>=P){
			//increament 'i' until i<R and the string pointed by i is less than pivot element(*R)
			while( i<R && *i <=*R){
				i++;		
			}
			//decreament 'j' until j>=P and the string pointed by j is greater than pivot element(*R) 
			while( j>=P && *j > *R ){				
			 	j--;
			}
			//Swap the element of i and j, only if i<j
			if(i<j){
				swap_function(i, j);
			}
		}
		//Finally swap the final position of i with pivot element in R
		swap_function(i, R);
		return i;
	
	}

}


string* quicksort(string* array_, string *P, string *R){
//Quicksort function: Take in three arguments, Pointer to the first element in the array, pointer to first element in the array and pointer to the last element in the array
	
	//Function is called recursively till P<R
	if(P<R){
		//Calling the partion function
		string* Q=partition_(P, R);
		//Recursively calling quicksort on sub-array after partition
	 	quicksort(array_, P, Q-1);
	    quicksort(array_, Q+1, R);

	}
	//Returning pointer to the first element in the sorted array
	return array_;
	
}

/*End of Functions related to quick sort */



