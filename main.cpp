#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "Core/autoloader"

using namespace std;

DataMaker D;
fstream &fin = D.getFin();
fstream &fout = D.getFout();

void fun1(int id)
{
	int a = rand(1, id), b = rand(id, 10);
	cout << a << ' ' << b << endl;
	fin << a << endl;
	fin << b << endl;
	fout << a + b << endl;
}

void fun2(int id)
{
	int a = rand(0, 1000000 * id * id * id), b = rand(0, 1000000 * id * id * id);
	cout << a << ' ' << b << endl;
	fin << a << endl;
	fin << b << endl;
	D.runStandardProgram();
}

int main()
{
	D.setName("AplusB")
			.setStandardCodeName("std.cpp")
			.setMethod(1, 3, fun1)
			.setMethod(10, fun2);
	
	D.generate();
	
	return 0;
}

