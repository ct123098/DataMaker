# DataMaker

*produced by ChenTong*

[Download](https://github.com/ct123098/DataMaker/archive/master.zip)




## What is this?

A small tool which can help you generating test data.

TODO~~~

## How to use it?

### DataMaker Class (DataMaker.h/cpp)

#### Constructor

`void DataMaker()`



#### Settings

##### compulsory

`DataMaker &setName(string _name)`To set the name of the problem.



##### optional

`DataMaker &setTmpDir(string _name)`

`DataMaker &setDataDir(string _name)`



`DataMaker &setStandardName(string _name)`To set the name of the standard code.

`DataMaker &setForceName(string _name)`To set the name of the brute force code.



#### Custom function

##### form

 `typedef void(*CustomFunctionPointer)(int);`

You can write your functions to generate data according to your purpose. Your functions must be written as`void fun(int id)`. These functions will be used when the function `generate()` be called.

| Parameter Name | type | compulsory/optional | description                      |
| -------------- | ---- | ------------------- | -------------------------------- |
| id             | int  | compulsory          | the number of this group of data |



##### setting method

`DataMaker& setMethod(int l, int r, CustomFunction fun)`

| Parameter Name | type           | compulsory/optional | description                              |
| -------------- | -------------- | ------------------- | ---------------------------------------- |
| l              | int            | compulsory          | the lower bound                          |
| r              | int            | compulsory          | the upper bound                          |
| fun            | CustomFunction | compulsory          | the function well be used to generate groups of data whose index belong to the interval [l, r] |

`DataMaker &setMethod(int x, CustomFunction fun)` can also be used to set a single test data.



#### Generate

`void DataMaker::generate(void)` 

When you have finished all the setting, you can call this function.

You will be given a information list with all the parameters. After confirming it, you can wait for the test data.



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

##### Basic Informations

`string getOS()`

`string getPathSeparator()`



##### Statements

`string compile(string source, string exec)`

`string run(string exec)`

`string makeDirectory(string name)`

`string removeDirectory(string name)`

`string removeFile(string name)`

`string redirectInput(string name)`

`string redirectOutput(string name)`



##### Conditions

`string fileExist(string file)`

`string fileNotExist(string file)`



##### Selection

`string selectionIf(string condition, string statement)`

`string selectionElse(string condition, string statement)`

`string selectionIfElse(string condition, string statement1, string statement2)`



TODO~~~


## Example

main.cpp
```c++
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

```
