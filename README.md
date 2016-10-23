# DataMaker

*produced by ChenTong*


## What is this?

A small tool which can help you generating data.

TODO~~~

## How to use it?

### DataMaker Class (DataMaker.h/cpp)

#### Constructor

`void DataMaker::DataMaker(string _name, int _lower, int _upper, string _stdName, string _forceName)`

| Parameter Name | type   | compulsory/optional | description                              |
| -------------- | ------ | ------------------- | ---------------------------------------- |
| _name          | string | compulsory          | the name of the problem                  |
| _lower         | int    | compulsory          | the lower bound of the data number       |
| _upper         | int    | compulsory          | the upper bound of the data number       |
| _stdName       | string | optional            | the name of the standard code            |
| _forceName     | string | optional            | the name of the code using brute force algorithm |

#### Settings

`DataMaker &setTmpDir(string _name)`

`DataMaker &setName(string _name)`To set the name of the problem.

`DataMaker &setBound(int _lower, int _upper)`To set the bound of the data number.

`DataMaker &setStandardName(string _name)`To set the name of the standard code.

`DataMaker &setForceName(string _name)`To set the name of the code using brute force algorithm.



#### Custom function

 `typedef void(*CustomFunction)(int);`

You can write your functions to generate data according to your purpose. Your functions must written as`void fun(int id)`. These functions well be used when the function `generate()` be called.

| Parameter Name | type | compulsory/optional | description                      |
| -------------- | ---- | ------------------- | -------------------------------- |
| id             | int  | compulsory          | the number of this group of data |



`DataMaker& setMethod(int l, int r, CustomFunction fun)`

`DataMaker &setMethod(int x, CustomFunction fun)`

| Parameter Name | type           | compulsory/optional | description                              |
| -------------- | -------------- | ------------------- | ---------------------------------------- |
| l              | int            | compulsory          | the lower bound                          |
| r              | int            | compulsory          | the upper bound                          |
| fun            | CustomFunction | compulsory          | the function well be used to generate groups of data whose index belong to the interval [l, r] |



#### Generate

`void DataMaker::generate(void)` 

When you have finished all the setting, you can call this function and wait for the data.



### some useful functions (functions.h/cpp)

These functions may help you a lot.

#### Random

`int randInt()` Generate a random integer form [0, 2^30^).

`long long randLongLong()` Generate a random integer form [0, 2^60^).

`double randDouble()` Generate a random real number form [0, 1).



`int rand(int l, int r)` Generate a random integer from [l, r] . 

`long long rand(long long l, long long r)` Generate a random integer from [l, r]. 

`double rand(double l, double r)` Generate a random real number form [l, r).

(You should ensure that l is not more than r)



`string randString(int len)` Generate a random string with small letter.

`string randString(int len, char st, char ed)` Generate a random string with character between st and ed.



#### string operators

`string + int` `string + double` `int + string` `double + string` are available.



#### system

`int system(string cmd)` You can use `string` to call `system()`.



`string getOS()`

`string getPathSeparator()`

`string compile(string source, string exec)`

`string run(string exec)`

`string makeDirectory(string name)`

`string removeDirectory(string name)`

`string removeFile(string name)`

`string redirectInput(string name)`

`string redirectOutput(string name)`



TODO~~~


## Example

main.cpp
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "Core/DataMaker.cpp"
#include "Core/functions.cpp"

using namespace std;

DataMaker D("AplusB", 1, 10);
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
	D.setStandardName("std.cpp")
			.setMethod(1, 4, fun1)
			.setMethod(5, 10, fun2);
	
	D.generate();
	
	return 0;
}
```
