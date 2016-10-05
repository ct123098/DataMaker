#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <ctime>

#include "DataMaker.h"

using namespace std;

void fun1(DataMaker &D, int id)
{
	int a = rand(1, id), b = rand(id, 10);
	D.fin << a << endl;
	D.fin << b << endl;
	
	D.fout << a + b << endl;
}

void fun2(DataMaker &D, int id)
{
	int a = rand(0, id * id * id * id), b = rand(0, id * id * id * id);
	D.fin << a << endl;
	D.fin << b << endl;
	
	D.fout << a + b << endl;
}

int main()
{
	srand(time(0));
	DataMaker D("problem", 10);
	D.setMethod(1, 5, fun1);
	D.setMethod(6, 10, fun2);
	D.generate();
	
	return 0;
}

