# DataMaker

*produced by ChenTong*


## What is this?

A small tool which can help you generating data.

TODO~~~

## How to use it?

### DataMaker Class (DataMaker.h/cpp)

#### Constructor

`void DataMaker::DataMaker(string _name, int _number, )`

#### Settings

`DataMaker& setName(string _name)` TODO

`DataMaker& setNumber(int _number)`TODO

`DataMaker& setStandardName(string _name)`TODO

`DataMaker& setForceName(string _name)`TODO



#### Custom functions

You can write your functions to generate data according to your purpose. Your functions must written as `void (DataMaker&, int)`

the parameter `DataMaker&` represent the instance you declared, and the `int` represent the number of this group of data.



`DataMaker& setMethod(int l, int r, void (*)(DataMaker&, int))`TODO





#### Generate

`void DataMaker::generate(void)` TODO



### some useful functions (functions.h/cpp)

These functions may help you a lot.

#### Random

`int rand(int l, int r)` Generate a random integer from [l, r] (You should ensure that l is not more than r). 

`double randDouble()` Generate a random real number form [0, 1).

`double randDouble(double l, double r)` Generate a random real number form [l, r) (You should ensure that l is not more than r).

`string randString(int len)` Generate a random string with small letter.

`string randString(int len, char st, char ed)` Generate a random string with character between st and ed.

#### string operators

`string + int` `string + double` `int + string` `double + string` are available.

#### system

`int system(string cmd)` You can use `string` to call `system()`.



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
