# DataMaker

*produced by ChenTong*


## What is this?

A small tool which can help you generating data.

TODO~~~

## How to use it?

### DataMaker Class (DataMaker.h/cpp)

#### Constructor

`void DataMaker::DataMaker(string _name, int _number, string _stdName, string _forceName)`

| Parameter Name | type   | compulsory/optional | description                              |
| -------------- | ------ | ------------------- | ---------------------------------------- |
| _name          | string | compulsory          | the name of the problem                  |
| _number        | int    | compulsory          | the total of the data group              |
| _stdName       | string | optional            | the name of the standard code            |
| _forceName     | string | optional            | the name of the code using brute force algorithm |

#### Settings

`DataMaker& setName(string _name)` To set the name of the problem.

`DataMaker& setNumber(int _number)`To set the total of the data group.

`DataMaker& setStandardName(string _name)`To set the name of the standard code.

`DataMaker& setForceName(string _name)`To set the name of the code using brute force algorithm.



#### Custom functions

You can write your functions to generate data according to your purpose. Your functions must written as `void (DataMaker&, int)`. These functions well be used when the function `generate()` be called.

| Parameter Name                | type       | compulsory/optional | description                              |
| ----------------------------- | ---------- | ------------------- | ---------------------------------------- |
| *Coustom* (`D` is recommend)  | DataMaker& | compulsory          | the DataMaker instance you have declared |
| *Coustom* (`id` is recommend) | int        | compulsory          | the number of this group of data         |



`DataMaker& setMethod(int l, int r, void (*fun)(DataMaker&, int))`

| Parameter Name | type                      | compulsory/optional | description                              |
| -------------- | ------------------------- | ------------------- | ---------------------------------------- |
| l              | int                       | compulsory          | the lower bound                          |
| r              | int                       | compulsory          | the upper bound                          |
| fun            | void (*)(DataMaker&, int) | compulsory          | the function well be used to generate groups of data whose index belong to the interval [l, r] |



#### Generate

`void DataMaker::generate(void)` 

When you have finished all the setting, you can call this function and wait for the data.



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
