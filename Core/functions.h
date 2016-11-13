#ifndef DATAMAKER_FUNCTIONS_H
#define DATAMAKER_FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>

using namespace std;

// rand extension
extern int randInt();

extern long long randLongLong();

extern double randDouble();

extern int rand(int l, int r);

extern long long rand(long long l, long long r);

extern double rand(double l, double r);

extern string randString(int len, char st = 'a', char ed = 'z');


//system commands extension
extern int system(const string &cmd);


// overload string + int/double
extern string operator +(const string &s, const int &a);

extern string operator +(const string &s, const double &a);

extern string operator +(const int &a, const string &s);

extern string operator +(const double &a, const string &s);


// throw an exception
extern void error(const string &err);


#endif //DATAMAKER_FUNCTIONS_H
