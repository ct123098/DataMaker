#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "Core/DataMaker.h"

// optional - load cpp files
#include "Core/autoloader"

using namespace std;

DataMaker D;
fstream &fin = D.getInFstream();
fstream &fout = D.getOutFstream();

// parameters
int par[6][5] = {
		// id, minA, maxA, minB, maxB
		{0},
		{1, -10, 20, 0, 0},
		{2, 0, 0, -10, 20},
		{3, -100, 100, -100, 100},
		{4},
		{5, -0x1f1f1f1f, -0x10101010, -0x1f1f1f1f, -0x10101010}
};

void fun1(int id)
{
	int minA = par[id][1], maxA = par[id][2], minB = par[id][3], maxB = par[id][4];
	int a = rand(minA, maxA), b = rand(minB, maxB);
	cout << a << ' ' << b << endl;

	fin << a << endl;
	fin << b << endl;
	fout << a + b << endl;
}

void fun2(int id)
{
	int minA = par[id][1], maxA = par[id][2], minB = par[id][3], maxB = par[id][4];
	int a = rand(minA, minB), b = rand(minB, maxB);
	cout << a << ' ' << b << endl;

	fin << a << endl;
	fin << b << endl;
	D.runStandardProgram();
}

int main()
{
	D.setName("AplusB")
			.setStandardCodeName("standard_AplusB.cpp")
			.setMethod(1, 3, fun1)
			.setMethod(5, fun2);

	D.generate();

	return 0;
}
