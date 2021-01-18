//Jay Shri Ram //Om Hum Hanumate Namah

//Including the required Header Files
#include <iostream>
#include "projectHeader.h"
#include <string>
#include <cstring>
#include <iomanip>
#include <chrono>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::flush;
using std::strncpy;
using std::stoi;
using namespace std::chrono;

#define	CAT_NAME_LEN	100
#define	APP_NAME_LEN	100
#define	VERSION_LEN	25
#define	UNIT_SIZE	3


//Starting the main Function

int main(){

	/*Declaring the necessary Variables */
	int numberCategories=0;						//Initializing the variable to store the number of categories
	int numberofApps=0;							//Initializing the variable to store the number of Apps to the myAppStore
	char categoryName[CAT_NAME_LEN];			//Initializing a char array variable to store category Name
	char categoryName_input[CAT_NAME_LEN];
	char inputCategory[CAT_NAME_LEN];			//Initializing a char array variable to store the category name while reading the app details
	categories *categoriesPtr=NULL; 			//Initializing the pointer to objects of "categories" type. This pointer is later on used to create new dynamic memory to store all categories
	tree *subTreePtr=NULL; 						//Initializing an array/Pointer to store the sub-trees
	hash_table_entry **hashTablePtr=NULL;		//Initializing an array of pointer to Store the pointer to object of type hash_table_entry
	hash_table_entry *hashTableObjectPtr=NULL;	//Initializing an array/Pointer to Store the object of type hash_table_entry objects
	string line;
	string word;

	/*Declaring Variables to read App Information from the INPUT OR SEACRH*/
	char appCategory[CAT_NAME_LEN];
	char appName[APP_NAME_LEN];
	char appName_input[APP_NAME_LEN];
	char appVersion[VERSION_LEN];
	float appSize;
	char appSizeUnits[UNIT_SIZE];
	float appPrice;



	//Getting the first input of the input file. Its the total number of categories
	getline(cin, line);
	numberCategories=stoi(line); //Coverting the string to an integer


	//Creating a Dynamic Memory to Store Category Type
	categoriesPtr=new categories[numberCategories];
	
	//Looping over number of categories
	for (int i=0; i<numberCategories;i++){
		//Reading the category Name
		getline(cin,line);
		
		//Coverting the String to the Character Array
		convertStringtoCharArray(categoryName, line, CAT_NAME_LEN);

		//Storing the Category name in the data structure using pointers
		strncpy((categoriesPtr+i)->category,categoryName, CAT_NAME_LEN);	
	}

	//Getting the Input of Number of Apps which will be read;
	getline(cin,line);
	numberofApps=stoi(line);
	
	//Creating a Dynamic Memory to Store objects of app_info, subTree and hash_table_entry
	subTreePtr = new tree[numberofApps];
	hashTableObjectPtr = new hash_table_entry[numberofApps];

	//Calculating the size of of hash table
	int sizeHashTable = 2*numberofApps;
	sizeHashTable = nearestLargerPrime(sizeHashTable);

	//Creating a dynamic array of to create a table
	hashTablePtr= new hash_table_entry*[sizeHashTable];
	//Iterating over all the apps
	for(int i=0; i<numberofApps; i++){
		
		//Reading the Category of the input
		getline(cin,line);
		convertStringtoCharArray(inputCategory, line, CAT_NAME_LEN);

		/*Variable below and the while loop following it, is being used to match the input category with the 'categories' dynamic array*/
		int j=0;
		while(j<numberCategories){

			//One found we break the loop
			if(strncmp(inputCategory,(categoriesPtr+j)->category, CAT_NAME_LEN)==0){
				break;
			}
			//Incrementing the Counter
			j++;
		}

		//The commands below reads all the app informations and stores them in the app_info data structure of the 'tree' object.
		strncpy(appCategory, inputCategory,CAT_NAME_LEN);
		strncpy((subTreePtr+i)->record.category, appCategory,CAT_NAME_LEN);	


		getline(cin,line);
		convertStringtoCharArray(appName,line, APP_NAME_LEN);
		strncpy((subTreePtr+i)->record.app_name, appName, APP_NAME_LEN);	
		
		getline(cin,line);
		convertStringtoCharArray(appVersion,line, VERSION_LEN);
		strncpy((subTreePtr+i)->record.version, appVersion, VERSION_LEN);

		getline(cin, line);
		appSize=stof(line);
		(subTreePtr+i)->record.size=appSize;

		getline(cin,line);
		convertStringtoCharArray(appSizeUnits,line, UNIT_SIZE);
		strncpy((subTreePtr+i)->record.units, appSizeUnits, UNIT_SIZE);

		getline(cin, line);
		appPrice=stof(line);
		(subTreePtr+i)->record.price=appPrice;

		//Inseting the app info in the binary search tree
		insert_BinarySearchTree(categoriesPtr+j, subTreePtr+i);


		//Storing the hash_table_entry object in the hashTableObjectPtr dynamic array 
		// Note this array is NOT the Hash Table. This array only stores the objects of hash_table_entry type
		strncpy((hashTableObjectPtr+i)->app_name, appName, APP_NAME_LEN);
		(hashTableObjectPtr+i)-> app_node = subTreePtr+i;
		
		//Calling the function for entry to hash table
		hashTable((hashTableObjectPtr+i), hashTablePtr, sizeHashTable);

	}

	while(cin>>word){
		if(word=="find"){
			cin>>word>>std::ws;
			if(word=="app"){
				getline(cin, word);
				resetCharArray(appName_input,APP_NAME_LEN);  //Resetting the variable.
				convertStringtoCharArray(appName_input, word, APP_NAME_LEN);
				searchHashTable(appName_input, hashTablePtr, sizeHashTable);
			}
			else if(word=="category"){
				getline(cin, word);
				resetCharArray(categoryName_input,CAT_NAME_LEN); //Resetting the variable
				convertStringtoCharArray(categoryName_input, word, CAT_NAME_LEN);
				search_BinarySearchTree(categoryName_input, categoriesPtr,numberCategories);
			}
			else if(word=="price"){
				freeApps(categoriesPtr,numberCategories); //Calling the function to search for free apps
			}
		}
		else if(word=="range"){

			char temp;
			cin>>temp;
			getline(cin,word, '\"');
			
			resetCharArray(categoryName_input,CAT_NAME_LEN); //Resetting the variable		
			convertStringtoCharArray(categoryName_input, word, CAT_NAME_LEN);
			
			cin>>word>>std::ws; //Reading if searches by app name or price
		
			if(word=="price"){
				float low,high;
				cin>>low>>std::ws;
				cin>>high>>std::ws;
				rangeSearchPrice(categoriesPtr, categoryName_input, low, high, numberCategories);
			}
			else if(word=="app"){
				string begin,end;
				char beginChar[APP_NAME_LEN], endChar[APP_NAME_LEN];
				
				resetCharArray(beginChar,APP_NAME_LEN);
				resetCharArray(endChar,APP_NAME_LEN);
				cin>>begin>>std::ws;
				cin>>end>>std::ws;

				resetCharArray(beginChar, APP_NAME_LEN);
				resetCharArray(beginChar, APP_NAME_LEN);

				convertStringtoCharArray(beginChar, begin, APP_NAME_LEN);
				convertStringtoCharArray(endChar, end, APP_NAME_LEN);

				rangeSearchApp(categoriesPtr, categoryName_input, beginChar, endChar, numberCategories);
				
			}
		}
		else if(word=="delete"){
			resetCharArray(categoryName_input,CAT_NAME_LEN); //Resetting the variable.
			resetCharArray(appName_input,APP_NAME_LEN);  //Resetting the variable.
			

			char temp;
			cin>>temp;
			getline(cin,word, '\"'); //Reading the category name
			
			convertStringtoCharArray(categoryName_input, word, CAT_NAME_LEN); //Coverting to char array
			
			cin>>temp;
			getline(cin,word, '\"'); //Reading the app name
			
			convertStringtoCharArray(appName_input, word, APP_NAME_LEN); //Converting to char array			
			deleteApp(categoriesPtr, hashTablePtr, categoryName_input, appName_input, numberCategories, sizeHashTable); //Calling the delete function.
		}
		
		else if(word=="no"){
			// Case for no report command
			cin>>word;
		}
		else if(word=="report"){
			//Case for report generation command

			for(int i=0; i<numberCategories; i++){
				cout<<"Category: "<<(categoriesPtr+i)->category<<endl;
				int numberofApps;
				int heightOfTree_;
				int heightOfLeftSubTree=0;
				int heightOfRightSubTree=0;
				if((categoriesPtr+i)->root!=0){
					numberofApps=findNumberOfApps((categoriesPtr+i)->root,(categoriesPtr+i)->root);
					heightOfTree_= heightOfTree((categoriesPtr+i)->root, (categoriesPtr+i)->root, (categoriesPtr+i)->root);
					if(((categoriesPtr+i)->root->left)!=0){
						heightOfLeftSubTree= heightOfTree(((categoriesPtr+i)->root->left), ((categoriesPtr+i)->root->left), ((categoriesPtr+i)->root->left));
					}
					if(((categoriesPtr+i)->root->right)!=0){
						heightOfRightSubTree= heightOfTree(((categoriesPtr+i)->root->right), ((categoriesPtr+i)->root->right), ((categoriesPtr+i)->root->right));
					}
				}
				else{
					numberofApps=0;
					heightOfTree_=0;
					heightOfLeftSubTree=0;
				    heightOfRightSubTree=0;
				}

				cout<<"Number of Nodes: "<< (numberofApps)<<endl;
				cout<<"Height of the Binary Tree: "<< heightOfTree_<<endl;
				cout<<"Height of the Left Sub Tree: "<< heightOfLeftSubTree<<endl;
				cout<<"Height of the Right Sub Tree: "<< heightOfRightSubTree<<endl;
				cout<<'\n';
			}
			int A[sizeHashTable]={0};
			float numberofApps =0;
			for(int i=0; i<sizeHashTable;i++){
				int chainLen=0;
				hash_table_entry *currentHashTableObjectPtr= *(hashTablePtr+i);
				if(currentHashTableObjectPtr!=0){
					chainLen=lengthOfTheHashChain(currentHashTableObjectPtr);
				}
				A[chainLen]=A[chainLen]+1;
			}
			for(int i=0; i<sizeHashTable;i++){
				if(A[i]!=0){
					cout<<"Number of Chains of length "<< i <<" :"<<A[i]<<endl;
				}
				if(i!=0){
					numberofApps=numberofApps+A[i]*i;
				}
			}
			cout<<"Load Factor: "<< numberofApps/sizeHashTable<<endl;
			cout<<'\n'<<endl;
			//Array to store all the app names;
			char categoryName[CAT_NAME_LEN];
			char appName[APP_NAME_LEN];
			for(int i=0; i<sizeHashTable;i++){
				hash_table_entry *currentHashTableObjectPtr= *(hashTablePtr+i);
				if(currentHashTableObjectPtr!=0){
					while(currentHashTableObjectPtr!=0){
						strcpy(appName,currentHashTableObjectPtr->app_name);
						strcpy(categoryName,(currentHashTableObjectPtr->app_node->record).category);
						

						//--------------Searching in Hashtable---------------
						high_resolution_clock::time_point t1 = high_resolution_clock::now();
						bool found=findApp_HashTable(appName, hashTablePtr, sizeHashTable);
						high_resolution_clock::time_point t2 = high_resolution_clock::now();
						duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
						cout<<appName<<" found in HASHTABLE in time: "<<time_span.count()*1000000<<endl;
						
						//---------------Searching in Binary Tree ------------------------

						high_resolution_clock::time_point t3 = high_resolution_clock::now();
						found=findApp_BinaryTree(categoriesPtr, categoryName,appName,numberCategories);

						high_resolution_clock::time_point t4 = high_resolution_clock::now();
						time_span = duration_cast<duration<double>>(t4 - t3);
						cout<<appName<<" found in BINARY TREE in time: "<<time_span.count()*1000000<<endl;

						cout<<'\n';

						currentHashTableObjectPtr=currentHashTableObjectPtr->next;
					}
				}
			}
		}	
	}

	// Deleting the Dyanmic Memories
	delete [] categoriesPtr;
	delete [] subTreePtr;
	delete [] hashTablePtr;
	delete [] hashTableObjectPtr;

	return 0;
}