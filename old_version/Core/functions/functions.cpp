#include "functions.h"

// rand extension

int randInt()
{
	return (((rand() & 32767) << 15) | (rand() & 32767));
}

long long randLongLong()
{
	return ((long long) randInt() << 30) | (long long) randInt();
}

double randDouble()
{
	return (double) randInt() / (1 << 30);
}

int rand(int l, int r)
{
	if(l > r)
		error("rand(int, int) : l is bigger than r");
	return randInt() % (r - l + 1) + l;
}

long long rand(long long l, long long r)
{
	if(l > r)
		error("rand(long long, long long) : l is bigger than r");
	return randLongLong() % (r - l + 1) + l;
}

double rand(double l, double r)
{
	if(l > r)
		error("rand(double, double) : l is bigger than r");
	return randDouble() * (r - l) + l;
}

string randString(int len, char st, char ed)
{
	if(len < 0)
		error("randString() : len can't be a negative number");
	if(st > ed)
		error("randString() : st is bigger than ed");
	string ret = "";
	for(int i = 1; i <= len; i++)
		ret += (char) rand((int) st, (int) ed);
	return ret;
}


//system commands extension
int system(const string &cmd)
{
//	cout << "system() : " << cmd << endl;
	return system(cmd.c_str());
}


// overload string + int/double
string operator +(const string &s, const int &a)
{
	char tmp[10];
	sprintf(tmp, "%d", a);
	return s + tmp;
}

string operator +(const string &s, const double &a)
{
	char tmp[10];
	sprintf(tmp, "%lf", a);
	return s + tmp;
}

string operator +(const int &a, const string &s)
{
	return s + a;
}

string operator +(const double &a, const string &s)
{
	return s + a;
}


// throw an exception
void error(const string &err)
{
	cout << "!!! Error encountered : " << err << " !!!" << endl;
	exit(1);
}

