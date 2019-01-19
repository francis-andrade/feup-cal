#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


#ifndef UTILITIES_H_
#define UTILITIES_H_

#include<string>
using namespace std;



long long smallestpower(int base,int n);
long long pow(int base, int e);
void printSquareArray(int ** arr, unsigned int size);
string removespaces(string s);
bool isInteger(const string & s);
int convint(string s);
int editDistance(const string & pattern,const string & text);







#endif
