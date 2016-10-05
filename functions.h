#ifndef DATAMAKER_FUNCTIONS_H
#define DATAMAKER_FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>

using namespace std;

// rand extension
int rand(int l, int r);

double randDouble();

double randDouble(double l, double r);

string randString(int len, char st = 'a', char ed = 'z');


//system extension
int system(const string &cmd);

// overload string + int/double
string operator +(const string &s, const int &a);

string operator +(const string &s, const double &a);

string operator +(const int &a, const string &s);

string operator +(const double &a, const string &s);

// throw an exception
void error(const string &err);

#endif //DATAMAKER_FUNCTIONS_H
