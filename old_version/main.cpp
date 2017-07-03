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
int par[0][0] = {
		// TODO
};

void fun1(int id) // TODO
{
	int n = 0, m = 0;

	fin << n << ' ' << m << endl;

	fout << 0 << endl;
}

void fun2(int id) // TODO
{
	int n = 0, m = 0;

	fin << n << ' ' << m << endl;

	D.runStandardProgram();
}

int main()
{
	// TODO
	D.setName("{problem name}")
			.setStandardCodeName("{standard code name}.cpp")
			.setMethod(1, 3, fun1)
			.setMethod(10, fun2);

	D.generate();

	return 0;
}
