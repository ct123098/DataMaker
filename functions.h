#ifndef DATAMAKER_FUNCTIONS_H
#define DATAMAKER_FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>

using namespace std;

// rand extension
int randInt();

long long randLongLong();

double randDouble();

int rand(int l, int r);

long long rand(long long l, long long r);

double rand(double l, double r);

string randString(int len, char st = 'a', char ed = 'z');


//system commands extension
int system(const string &cmd);

string getOS();

string getPathSeparator();

string compile(const string &source, const string &exec);

string run(const string &exec);

string makeDirectory(const string &name);

string removeDirectory(const string &name);

string removeFile(const string &name);

string redirectInput(const string &name);

string redirectOutput(const string &name);



// overload string + int/double
string operator +(const string &s, const int &a);

string operator +(const string &s, const double &a);

string operator +(const int &a, const string &s);

string operator +(const double &a, const string &s);

// throw an exception
void error(const string &err);

#endif //DATAMAKER_FUNCTIONS_H
