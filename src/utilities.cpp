#include "utilities.h"
#include <iostream>
#include <limits>
#include <typeinfo>
#include<vector>
const int INT_INFINITY = INT_MAX;
using namespace std;

long long smallestpower(int base,int n){
	long long k=1;
	int i=0;
	while(k<=n){
		k=k*base;
		i++;
	}
	return k;
}

long long pow(int base, int e){
	int r=1;
	for(int i=0;i<e;i++){
		r=r*e;
	}
	return r;
}


void printSquareArray(int ** arr, unsigned int size)
{
	for(unsigned int k = 0; k < size; k++)
	{
		if(k == 0)
		{
			cout <<  "   ";
			for(unsigned int i = 0; i < size; i++)
				cout <<  " " << i+1 << " ";
			cout << endl;
		}

		for(unsigned int i = 0; i < size; i++)
		{
			if(i == 0)
				cout <<  " " << k+1 << " ";

			if(arr[k][i] == INT_INFINITY)
				cout << " - ";
			else
				cout <<  " " << arr[k][i] << " ";
		}

		cout << endl;
	}
}


string removespaces(string s){
	unsigned int i = 0;
	//the following loop removes newlines
	while (i < s.size()){
		if (s[i] == 10){
			s.erase(i, 1);
			i--;
		}
		i++;
	}
	i = 0;
	//The following loops transforms multiple spaces in only one space
	while (i+1 < s.size()){
		if (s[i] == ' ' && s[i + 1] == ' '){
			s.erase(i, 1);
			i = i - 1;
		}
		i = i + 1;
	}
	if ((s.size()>0) && s[0] == ' '){
		s.erase(0, 1);//deletes space at the beginning of a string
	}
	if ((s.size() > 0) && s[s.size()-1]==' '){
		s.erase(s.size() - 1, 1);//deletes space at the end of a string
	}
	return s;
}



/*
This functions checks if a string is an integer
parameter: const string &s-The function will check if this string is an integer
return value- true if string is an integer and false if not
source:http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
*/
bool isInteger(const string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}


/*
This function converts a string to an integer and returns -1 if string is not an integer
parameter: string s-string that is going to be converted
return value - integer that corresponds to the string
*/
int convint(string s) {
	if (!isInteger(s)) {
		return -1;
	}
	else {
		return stoi(s);
	}
}

int editDistance(const string & pattern,const string & text)
{
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}


