//Including the required Header Files
#include <iostream>
#include "projectHeader.h"
#include <string>
#include <cstring>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::strncpy;



void convertStringtoCharArray(char *charArray, string input, int maxLen){
/* This function converts a string to a Character Array*/
/* Takes in 3 arguments. charArray is the pointer to the first element in the array.
   Input is the string we wish to convert.
   maxLen is the maxLen of the string possible.	
*/
	const char *tempChar=input.c_str();
	if(tempChar[0]!='\"'){
		for (string::size_type j=0;j<maxLen;j++){
			*(charArray+j)=*(tempChar+j);
		}
	}
	else{
		for (string::size_type j=1;j<maxLen && *(tempChar+j)!='\"';j++){
			*(charArray+ j-1)=*(tempChar+j);
		}
	}
} 


void resetCharArray(char * word, int maxLen){
// This function resets the "word" and clears any possible letters in it
	for (int i=0; i< maxLen; i++){
		word[i]='\0';
	}
}

int nearestLargerPrime(int number){
/*This function calculates the nearest prime number larger than the input number*/

	int i=0; //Initializing the counter
	
	if(number==2){
		number+=3;
	}

	while(!TestForPrime(number+i)){
		i++;
	}
	return (number+i);
}


void insert_BinarySearchTree(categories *categoriesPtr, tree *subTree){
	//Checking if the tree has started yet or not
	if(categoriesPtr->root==0){
		//If the tree doesn't exist for that category, create one.
		categoriesPtr->root=subTree;	
	}

	else{
		//If it exists start a variable to keep track of the tree and insert at the new subTree at last postion of the existing Tree Structure

		tree *currentSubTree=categoriesPtr->root; 
		tree* parentSubTree=currentSubTree;
		while(currentSubTree!=0){
			if(strcmp(currentSubTree->record.app_name, subTree->record.app_name)>0){
				parentSubTree=currentSubTree;
				currentSubTree= currentSubTree->left;
				if(currentSubTree==0){
					parentSubTree->left=subTree;
				}
			}
			else if(strcmp(currentSubTree->record.app_name, subTree->record.app_name)==0){
				parentSubTree=currentSubTree;
				currentSubTree= currentSubTree->left;
				if(currentSubTree==0){
					parentSubTree->left=subTree;
				}
			}
			else{
				parentSubTree=currentSubTree;
				currentSubTree= currentSubTree->right;
				if(currentSubTree==0){
					parentSubTree->right=subTree;
				}
			}
		}
	}
}


int sumCharASCII(char *charArray){
/* Thus function sums the ASCII values of all the characters in the character array */

	int sum=0; //Initializing the Sum

	//Iterating over all the characters of the array 
	for(int i=0; charArray[i] != '\0'; i++){
		
		sum=sum + int((unsigned char) charArray[i]);
	}

	return sum;
}


void hashTable(hash_table_entry *hashTableObjectPtr, hash_table_entry **hashTablePtr, int sizeHashTable){
/* This function inserts pointer to the object of hash_table_entry type in the Hash Table*/

	//Calculating the key of the app using appName and sizeHashTable
	int sumASCII = sumCharASCII(hashTableObjectPtr->app_name); 	// Sum of the ASCII values of all tha characters in the array
	int KEY      = sumASCII % sizeHashTable; 			//Calculating the key
	//Inseting the object in the 'KEY' index of the hash table
	//If that Index doesn't point to any object of type hash_table_entry
	if(*(hashTablePtr + KEY)==0){
		*(hashTablePtr + KEY) = hashTableObjectPtr;
	}
	//If it points then use Separate Chaining
	else{
		/*	Update the 'next' object in the hash_table_entry object pointed by hashTableObjectPtr to point to the hash_table_entry 
			object currently pointed by the KEY index.
		*/
		hashTableObjectPtr->next= *(hashTablePtr+KEY); 
		//Update the KEY index in the Hash Table to point to the new inserted object of type hash_table_entry
		*(hashTablePtr + KEY)=hashTableObjectPtr;
	}
}


void searchHashTable(char *appName, hash_table_entry **hashTablePtr, int sizeHashTable){
/* This function searches for the appName in the Hash Table using the hashTablePtr*/

	//Calculating the key of the app using appName and sizeHashTable
	int sumASCII 	= sumCharASCII(appName); 				// Sum of the ASCII values of all tha characters in the array.
	int KEY      	= sumASCII % sizeHashTable; 			//Calculating the key.
	bool AppExists	= 0;								//Marker to indicate if the App Exists or Not. Starts with False.
	if(*(hashTablePtr+KEY)==0){
		cout<<"Application"<<" "<<appName<<" "<<"not found."<<endl;
		cout<<'\n';
	}
	else{

		hash_table_entry *currentHashTableObjectPtr= *(hashTablePtr+KEY);
		tree *nodeSubtreePtr;
		while(currentHashTableObjectPtr!=0){
			if(strcmp(currentHashTableObjectPtr->app_name, appName)==0){
				AppExists=1;
				nodeSubtreePtr=currentHashTableObjectPtr->app_node;
				break;
			}
			else{
				currentHashTableObjectPtr=currentHashTableObjectPtr->next;
			} 
		}

		if(AppExists){
			cout<<"Found Application: "<<appName<<endl;
			cout<<'\t'<<"Category: "<<(*nodeSubtreePtr).record.category<<endl;
			cout<<'\t'<<"Application Name: "<<(*nodeSubtreePtr).record.app_name<<endl;
			cout<<'\t'<<"Version: "<<(*nodeSubtreePtr).record.version<<endl;
			std::cout << std::setprecision(1) << std::fixed;
			cout<<'\t'<<"Size: "<<(*nodeSubtreePtr).record.size<<endl;
			cout<<'\t'<<"Units: "<<(*nodeSubtreePtr).record.units<<endl;
			std::cout << std::setprecision(2) << std::fixed;
			cout<<'\t'<<"Price: $"<<(*nodeSubtreePtr).record.price<<endl;
			cout<<'\n';
		}
		else{
			cout<<"Application"<<" "<<appName<<" "<<"not found."<<endl;
			cout<<'\n';
		}
	}

}

void inorderTraverseBinaryTree(tree *TreePtr){

	if(TreePtr->left!=0){
		inorderTraverseBinaryTree(TreePtr->left);
	}
	cout<<'\t'<<TreePtr->record.app_name<<endl;
	if(TreePtr->right!=0){
		inorderTraverseBinaryTree(TreePtr->right);
	}
} 

void search_BinarySearchTree(char *categoryName, categories *categoriesPtr, int numberCategories){


	int i=0;
	int categoryExists=0;
	while(i<numberCategories){
		if(strcmp((categoriesPtr+i)->category,categoryName)==0){
			categoryExists=1;
			break;
		}
		i++;
	}
	if(categoryExists){
		if((categoriesPtr+i)->root==0){
			cout<<"Category "<<categoryName<<" no apps found."<<endl;
			cout<<'\n';
		}
		else{
			cout<<"Category: "<<categoryName<<endl;
			inorderTraverseBinaryTree((categoriesPtr+i)->root);
			cout<<'\n';
		}
	}
	else{
		cout<<"Category "<< categoryName << " not found."<<endl;
	}
}

int inorderTraverseBinaryTree_FreePrice(tree *TreePtr, int count, categories *categoriesPtr ){
//Prints all the free apps and returns the number of them
	if(TreePtr->left!=0){
		count=inorderTraverseBinaryTree_FreePrice(TreePtr->left, count, categoriesPtr);
	}
	if(TreePtr->record.price==0){
		if(count==0){
			cout<<"Free Applications in Category: "<<categoriesPtr->category<<endl;
		}
		cout<<'\t'<<TreePtr->record.app_name<<endl;
		count+=1;
	}
	if(TreePtr->right!=0){
		count=inorderTraverseBinaryTree_FreePrice(TreePtr->right, count, categoriesPtr);
	}
	return count;
} 

void freeApps(categories *categoriesPtr, int numberCategories){
//This function prints free apps in each category

	for (int i=0; i<numberCategories;i++){
		// cout<<"Free Applications in Category: "<<(categoriesPtr+i)->category<<endl;

		if((categoriesPtr+i)->root==0){
			cout<<"No free applications found in category "<<(categoriesPtr+i)->category<<"."<<endl;
			cout<<'\n';
		}
		else{
			int count=0;
			count=inorderTraverseBinaryTree_FreePrice((categoriesPtr+i)->root, count, categoriesPtr+i);
			if(count==0){
				cout<<"No free applications found in category "<<(categoriesPtr+i)->category<<"."<<endl;
				cout<<'\n';
			}
			else{
				cout<<'\n';
			}
		}
	}	

}


int inorderTraverseBinaryTree_PriceRange(tree *TreePtr, int count, float low,float high, char *categoryName_input){
//Prints all the free apps and returns the number of them
	if(TreePtr->left!=0){
		count=inorderTraverseBinaryTree_PriceRange(TreePtr->left, count, low, high, categoryName_input);
	}
	if(TreePtr->record.price>=low && TreePtr->record.price<=high){
		if(count==0){
			cout<<"Applications in Price Range "<<"($"<<low<<","<<"$"<<high<<")"<<" in Category: "<< categoryName_input<<endl;
		}
		cout<<'\t'<<TreePtr->record.app_name<<endl;
		count+=1;
	}
	if(TreePtr->right!=0){
		count=inorderTraverseBinaryTree_PriceRange(TreePtr->right, count, low, high, categoryName_input);
	}
	return count;
} 


void rangeSearchPrice(categories *categoriesPtr, char *categoryName_input, float low,float high, int numberCategories){
	for(int i=0; i<numberCategories; i++){
		if(strcmp((categoriesPtr+i)->category, categoryName_input)==0){
			

			if((categoriesPtr+i)->root==0){
				cout<<"No applications found in "<<categoryName_input<<" for the given price range "<< "($"<<low<<","<<"$"<<high<<")."<<endl;
				cout<<'\n';
			}
			else{
				int count=0;
				count=inorderTraverseBinaryTree_PriceRange((categoriesPtr+i)->root, count,low, high, categoryName_input);
				if(count==0){
					cout<<"No applications found in "<<categoryName_input<<" for the given price range "<< "($"<<low<<","<<"$"<<high<<")."<<endl;
					cout<<'\n';
				}
				else{
					cout<<'\n';
				}
			}

			break;
		}
	}

}


int inorderTraverseBinaryTree_App(tree *TreePtr, int count, char *begin, char *end, char *categoryName_input){
//Prints all the free apps and returns the number of them
	if(TreePtr->left!=0){
		count=inorderTraverseBinaryTree_App(TreePtr->left, count, begin, end, categoryName_input);
	}
	if((strcmp(TreePtr->record.app_name, begin)==0 || strcmp(TreePtr->record.app_name, begin)>0) && (strcmp(TreePtr->record.app_name, end)==0 || strcmp(TreePtr->record.app_name, end)<0)){
		
		if(count==0){
			cout<<"Applications in Range "<<"("<<begin<<","<<end<<")"<<" in Category: "<< categoryName_input<<endl;
		}

		cout<<'\t'<<TreePtr->record.app_name<<endl;
		count+=1;
	}
	if(TreePtr->right!=0){
		count=inorderTraverseBinaryTree_App(TreePtr->right, count, begin, end, categoryName_input);
	}
	return count;
} 


void rangeSearchApp(categories *categoriesPtr, char *categoryName_input, char *begin, char *end, const int numberCategories){
	for(int i=0; i<numberCategories; i++){
		if(strcmp((categoriesPtr+i)->category, categoryName_input)==0){

			if((categoriesPtr+i)->root==0){
				cout<<"No applications found in "<<categoryName_input<<" for the given range "<< "("<<begin<<","<<end<<")."<<endl;
				cout<<'\n';
			}
			else{
				int count=0;
				count=inorderTraverseBinaryTree_App((categoriesPtr+i)->root, count,begin, end, categoryName_input);
				if(count==0){
					cout<<"No applications found in "<<categoryName_input<<" for the given range "<< "("<<begin<<","<<end<<")."<<endl;
					cout<<'\n';
				}
				else{
					cout<<'\n';
				}
			}

			break;
		}
	}
}



tree *SmallestNodeRightSubtree(tree *nodeSubtreePtr){
//This function returns the smallest node in th right subtree of the binary tree from the root
	tree *currentSubTree= nodeSubtreePtr->right; //Moving to the right subtree

	while(currentSubTree!=0){
		if(currentSubTree->left!=0){
			currentSubTree=currentSubTree->left;
		}
		else{
			break;
		}
	}
	return currentSubTree;
}


tree* inorderTraverseBinarydelete1(tree *nodeSubtreePtr, tree *nodeTreePtr,categories *categoriesPtr, tree *parentNode=0){

	if(categoriesPtr->root==nodeSubtreePtr){
		//If the tree doesn't exist for that category, create one.
		return categoriesPtr->root;	
	}

	else{
		//If it exists start a variable to keep track of the tree and insert at the new subTree at last postion of the existing Tree Structure

		tree* parentNode=nodeTreePtr;
		while(nodeTreePtr!=0 && strcmp(nodeTreePtr->record.app_name, nodeSubtreePtr->record.app_name)!=0){
			if(strcmp(nodeTreePtr->record.app_name, nodeSubtreePtr->record.app_name)>0){
				parentNode=nodeTreePtr;
				nodeTreePtr= nodeTreePtr->left;
			}
			else if(strcmp(nodeTreePtr->record.app_name, nodeSubtreePtr->record.app_name)==0){
				parentNode=nodeTreePtr;
				nodeTreePtr= nodeTreePtr->left;
			}
			else{
				parentNode=nodeTreePtr;
				nodeTreePtr= nodeTreePtr->right;
			}
		}
		return parentNode;
	}
}



void deleteNodeSearchTree(tree *nodeSubtreePtr, tree *nodeTreePtr, categories *categoriesPtr){
	
	tree *smallestNode=0;
	if(nodeSubtreePtr->left==0 && nodeSubtreePtr->right==0){ //If the node is a leaf node
		tree* parentNode=inorderTraverseBinarydelete1(nodeSubtreePtr, nodeTreePtr, categoriesPtr);


		if(nodeSubtreePtr==(categoriesPtr->root)){
			categoriesPtr->root=smallestNode;
		}

		else{
			if(parentNode==categoriesPtr->root){
				categoriesPtr->root=smallestNode;
			}
			else if(parentNode->left==nodeSubtreePtr){
				parentNode->left=smallestNode;
			}
			else if(parentNode->right==nodeSubtreePtr){
				parentNode->right=smallestNode;
			}
		}

	}
	else if(nodeSubtreePtr->left==0 && nodeSubtreePtr->right!=0){


		smallestNode=nodeSubtreePtr->right;
		tree* parentNode=inorderTraverseBinarydelete1(nodeSubtreePtr, nodeTreePtr, categoriesPtr); //If only right leaf node exits
		
		if(nodeSubtreePtr==(categoriesPtr->root)){
			categoriesPtr->root=smallestNode;
		}

		else{
			if(parentNode==categoriesPtr->root){
				if(categoriesPtr->root->left==nodeSubtreePtr){
					categoriesPtr->root->left=smallestNode;
				}
				else if(categoriesPtr->root->right==nodeSubtreePtr){
					categoriesPtr->root->right=smallestNode;
				}
			}
			else if(parentNode->left==nodeSubtreePtr){
				parentNode->left=smallestNode;
			}
			else if(parentNode->right==nodeSubtreePtr){
				parentNode->right=smallestNode;
			}

		}

	}
	else if(nodeSubtreePtr->left!=0 && nodeSubtreePtr->right==0){

		smallestNode=nodeSubtreePtr->left;
		tree* parentNode=inorderTraverseBinarydelete1(nodeSubtreePtr, nodeTreePtr, categoriesPtr); //If only right leaf node exits		

		
		if(nodeSubtreePtr==(categoriesPtr->root)){
			categoriesPtr->root=smallestNode;
		}

		else{

			if(parentNode==categoriesPtr->root){
				if(categoriesPtr->root->left==nodeSubtreePtr){
					categoriesPtr->root->left=smallestNode;
				}
				else if(categoriesPtr->root->right==nodeSubtreePtr){
					categoriesPtr->root->right=smallestNode;
				}
			}
			if(parentNode->left==nodeSubtreePtr){

				parentNode->left=smallestNode;
			}
			else if(parentNode->right==nodeSubtreePtr){

				parentNode->right=smallestNode;
			}
		} 
	}
	else{


		smallestNode=SmallestNodeRightSubtree(nodeSubtreePtr);
		tree *parentNodeOfSmallestNode=inorderTraverseBinarydelete1(smallestNode, nodeTreePtr, categoriesPtr);
		deleteNodeSearchTree(smallestNode, nodeTreePtr, categoriesPtr);
		smallestNode->left=nodeSubtreePtr->left;
		smallestNode->right=nodeSubtreePtr->right;
	
		tree* parentNode=inorderTraverseBinarydelete1(nodeSubtreePtr, nodeTreePtr, categoriesPtr); 
		
		if(nodeSubtreePtr==(categoriesPtr->root)){
			categoriesPtr->root=smallestNode;
		}

		else{
			if(parentNode==categoriesPtr->root){
				if(categoriesPtr->root->left==nodeSubtreePtr){
					categoriesPtr->root->left=smallestNode;
					nodeSubtreePtr=0;
				}
				else if(categoriesPtr->root->right==nodeSubtreePtr){
					categoriesPtr->root->right=smallestNode;
				}
			}
			if(parentNode->left==nodeSubtreePtr){

				parentNode->left=smallestNode;
			}
			else if(parentNode->right==nodeSubtreePtr){

				parentNode->right=smallestNode;
			}
		}	
	}
}


void searchHashTableDelete(char *categoryName_input, char *appName, hash_table_entry **hashTablePtr, int sizeHashTable,categories *categoriesPtr, tree *nodeTreePtr){
/* This function searches for the appName in the Hash Table using the hashTablePtr*/

	//Calculating the key of the app using appName and sizeHashTable
	int sumASCII 	= sumCharASCII(appName); 				// Sum of the ASCII values of all tha characters in the array.
	int KEY      	= sumASCII % sizeHashTable; 			//Calculating the key.
	bool AppExists	= 0;								//Marker to indicate if the App Exists or Not. Starts with False.
	if(*(hashTablePtr+KEY)==0){
		cout<<"Application "<<appName<<" not found in category "<<categoryName_input<<"; unable to delete."<<endl;
		cout<<'\n';
	}
	else{

		hash_table_entry *currentHashTableObjectPtr= *(hashTablePtr+KEY);
		hash_table_entry *parentHashTableObjectPtr=0;

		tree *nodeSubtreePtr;
		while(currentHashTableObjectPtr!=0){
			if(strcmp(currentHashTableObjectPtr->app_name, appName)==0){
				AppExists=1;
				nodeSubtreePtr=currentHashTableObjectPtr->app_node;
				break;
			}
			else{
				parentHashTableObjectPtr=currentHashTableObjectPtr;
				currentHashTableObjectPtr=currentHashTableObjectPtr->next;
			} 
		}

		if(AppExists){
			deleteNodeSearchTree(nodeSubtreePtr,nodeTreePtr, categoriesPtr);
			
			if(currentHashTableObjectPtr!=0){
				
				if(parentHashTableObjectPtr!=0){
					parentHashTableObjectPtr->next=currentHashTableObjectPtr->next;
				}
			
				else{
					*(hashTablePtr+KEY)=0;
				}	
				
			}
			else{
				parentHashTableObjectPtr->next=0;
			}
			cout<<"Application "<<appName<<" from Category "<< categoryName_input<<" successfully deleted."<<endl;
			cout<<'\n';

		}
		else{
			cout<<"Application "<<appName<<" not found in category "<<categoryName_input<<"; unable to delete."<<endl;
			cout<<'\n';
		}
	}

}


void deleteApp(categories *categoriesPtr, hash_table_entry **hashTablePtr, char *categoryName_input, char *appName_input, const int numberCategories, int sizeHashTable){
//This function deletes the app from the search tree and hashtable;
	
	int categoryFound=0;
	for(int i=0; i<numberCategories; i++){
		if(strcmp((categoriesPtr+i)->category, categoryName_input)==0){
			categoryFound=1;
			if((categoriesPtr+i)->root==0){
				cout<<"Application "<<appName_input<<" not found in category "<<categoryName_input<<"; unable to delete."<<endl;
				cout<<'\n';
			}
			else{
				searchHashTableDelete(categoryName_input, appName_input, hashTablePtr, sizeHashTable,categoriesPtr+i,(categoriesPtr+i)->root);
				break;
			}
		}
		
	}
	if(!categoryFound){
		cout<<"Application "<<appName_input<<" not found in category "<<categoryName_input<<"; unable to delete."<<endl;
		cout<<'\n';
	}

}



//-----------------------Functions below are used for generating reports and the characteristics of the data structures ------------------------------

int findNumberOfApps(tree *TreePtr, tree *rootTree){

	static int numberofApps=0;
	int finalNumberofApps=0;
	numberofApps++;
	
	if(TreePtr->left!=0){
		int apps=findNumberOfApps(TreePtr->left, rootTree);
	}
	if(TreePtr->right!=0){
		int apps=findNumberOfApps(TreePtr->right, rootTree);
	}
	

	if(TreePtr==rootTree){
		finalNumberofApps=numberofApps;
		numberofApps=0;
	}

	return finalNumberofApps;
}


int heightOfTree(tree *TreePtr,tree *nodeTreePtr, tree *parentNode){

	static int height=0;
	int finalHeight=0;
	
	if(TreePtr->left!=0){
		int apps=heightOfTree(TreePtr->left, nodeTreePtr, TreePtr);
	}
	if(TreePtr->right!=0){
		int apps=heightOfTree(TreePtr->right, nodeTreePtr, TreePtr);
	}
	
	if(TreePtr->left!=0 || TreePtr->right!=0){
		height++;
	}

	if(TreePtr==nodeTreePtr){
		finalHeight=height;
		height=0;
	}
	return finalHeight;
}

int lengthOfTheHashChain(hash_table_entry *currentHashTableObjectPtr){
	int lenChain=0;
	while(currentHashTableObjectPtr!=0){
		currentHashTableObjectPtr=currentHashTableObjectPtr->next;
		lenChain++;
	}
	return lenChain;
}	



bool findApp_HashTable(char *appName, hash_table_entry **hashTablePtr, int sizeHashTable){

	//Calculating the key of the app using appName and sizeHashTable
	int sumASCII 	= sumCharASCII(appName); 				// Sum of the ASCII values of all tha characters in the array.
	int KEY      	= sumASCII % sizeHashTable; 			//Calculating the key.
	bool AppExists	= 0;								//Marker to indicate if the App Exists or Not. Starts with False.
	if(*(hashTablePtr+KEY)==0){
		return 0;
	}
	else{

		hash_table_entry *currentHashTableObjectPtr= *(hashTablePtr+KEY);
		tree *nodeSubtreePtr;
		while(currentHashTableObjectPtr!=0){
			if(strcmp(currentHashTableObjectPtr->app_name, appName)==0){
				AppExists=1;
				nodeSubtreePtr=currentHashTableObjectPtr->app_node;
				break;
			}
			else{
				currentHashTableObjectPtr=currentHashTableObjectPtr->next;
			} 
		}

		if(AppExists){
			return 1;
		}
		else{
			return 0;
		}
	}


} 



int findAppinTree(tree *TreePtr,tree *nodeTreePtr,char *app_Name){

	static int found=0;
	int finalFound=0;
	
	if(TreePtr->left!=0){
		int apps=findAppinTree(TreePtr->left, nodeTreePtr, app_Name);
	}
	if(TreePtr->right!=0){
		int apps=findAppinTree(TreePtr->right,nodeTreePtr, app_Name);
	}

	if(strcmp((TreePtr->record).app_name, app_Name)==0){
		found++;
	}

	if(TreePtr==nodeTreePtr){
		finalFound=found;
		found=0;
	}
	return finalFound;
}


bool findApp_BinaryTree(categories *categoriesPtr, char *categoryName_input,char *app_Name, const int numberCategories){
	for(int i=0; i<numberCategories; i++){
		if(strcmp((categoriesPtr+i)->category, categoryName_input)==0){

			if((categoriesPtr+i)->root==0){
				return 1;
			}
			else{
				int count=0;
				count=findAppinTree((categoriesPtr+i)->root,(categoriesPtr+i)->root, app_Name);
				if(count==0){
					return 0;
				}
				else{
					return 1;
				}
			}

			break;
		}
	}
	return 1;
}