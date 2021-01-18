//Including the required libraries
#include <iostream>
#include "defn.h"
#include <string>
using std::string;

//Function Declarations

bool TestForPrime( int val );
void convertStringtoCharArray(char *line, string input, int maxLen);
void insert_BinarySearchTree(categories *categoriesPtr, tree *subTree);
int nearestLargerPrime(int number);
void hashTable(hash_table_entry *hashTableObjectPtr, hash_table_entry **hashTablePtr, int sizeHashTable);
void searchHashTable(char *appName, hash_table_entry **hashTablePtr, int sizeHashTable);
void search_BinarySearchTree(char *categoryName, categories *categoriesPtr, int numberCategories);
void resetCharArray(char * word, int maxLen);
void freeApps(categories *categoriesPtr, int numberCategories);
void rangeSearchPrice(categories *categoriesPtr, char *categoryName_input, float low,float high, int numberCategories);
void rangeSearchApp(categories *categoriesPtr, char *categoryName_input, char *begin, char *end, int numberCategories);
void deleteApp(categories *categoriesPtr, hash_table_entry **hashTablePtr, char *categoryName_input, char *appName_input, const int numberCategories, int sizeHashTable);


// Report Functions -------------------
int findNumberOfApps(tree *TreePtr, tree *rootTree);
int heightOfTree(tree *TreePtr,tree *nodeTreePtr, tree *parentNode);
int lengthOfTheHashChain(hash_table_entry *currentHashTableObjectPtr);
bool findApp_HashTable(char *appName, hash_table_entry **hashTablePtr, int sizeHashTable);
bool findApp_BinaryTree(categories *categoriesPtr, char *categoryName_input,char *app_Name, const int numberCategories);

