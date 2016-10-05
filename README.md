# DataMaker

*produced by ChenTong*


## What is this?

TODO~~~

## How to use it?

TODO~~~


## Example

main.cpp
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "DataMaker.cpp"
#include "functions.cpp"

using namespace std;

void fun1(DataMaker &D, int id)
{
	int a = rand(1, id), b = rand(id, 10);
	cout << a << ' ' << b << endl;
	D.fin << a << endl;
	D.fin << b << endl;
	D.fout << a + b << endl;
}

void fun2(DataMaker &D, int id)
{
	int a = rand(0, 1000000 * id * id * id), b = rand(0, 1000000 * id * id * id);
	cout << a << ' ' << b << endl;
	D.fin << a << endl;
	D.fin << b << endl;
	D.runStandardProgram();
}

int main()
{
	DataMaker D("AplusB", 10);
	
	D.setStandardName("std").setMethod(1, 4, fun1).setMethod(5, 10, fun2);
	D.generate();
	
	return 0;
}
```
