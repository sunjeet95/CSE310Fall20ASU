#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;



//Declaring the functions
string& cyclic_function(string& test_line, int shift);
string* insertion_sort(string *array_, string::size_type len);
int cluster(string *array_, int len_);
unsigned int binary_search(string& line, string *array_, int len_);
int decode_function(string *StringArray,string *SortedStringArray, int indexPosition, int totalLengthLine);
string* quicksort(string* array, string *P, string *R);
