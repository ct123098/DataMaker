#ifndef DATAMAKER_FUNCTIONS_H
#define DATAMAKER_FUNCTIONS_H

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cassert>


namespace datamaker
{
	using namespace std;

// rand extension
	extern bool rand_bool();

	extern int rand_int();

	extern long long rand_ll();

	extern double rand_double();

	extern int rand_range(int l, int r);

	extern long long rand_range(long long l, long long r);

	extern double rand_range(double l, double r);

	extern string rand_string(int len, char st = 'a', char ed = 'z');


//system commands extension
	extern int xsystem(const string &cmd);


//  overload string + int/double
	template<typename T1, typename T2>
	string operator + (const T1 &t1, const T2 &t2);


//	assert extension
	extern void xassert(bool expr, const string &msg);
}


#endif //DATAMAKER_FUNCTIONS_H
