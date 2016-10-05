#include "functions.h"

// rand extension
int rand(int l, int r)
{
	if(l > r)
		error("rand() : l is bigger than r");
	return (((rand() & 32767) << 15) | (rand() & 32767)) % (r - l + 1) + l;
}

double randDouble()
{
	return (double) rand(0, 1 << 30) / (1 << 30);
}

double randDouble(double l, double r)
{
	if(l > r)
		error("randDouble() : l is bigger than r");
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
		ret += (char) rand(st, ed);
	return ret;
}

//system extension
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

//string operator + (const char *a, const char *b)
//{
//	return string() + a + b;
//}
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
	cout << "Error encountered : " << err << endl;
	exit(1);
}


