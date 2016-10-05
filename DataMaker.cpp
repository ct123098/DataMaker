#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

#include "DataMaker.h"

using namespace std;

// DataMaker
DataMaker::DataMaker(string _name, int _number, string _stdName)
{
	setName(_name);
	setNumber(_number);
	setStdName(_stdName);
	fin.clear(); fout.clear();
	inputFile = outputFile = "";
}
void DataMaker::setName(string _name)
{
	name = _name;
	dataDir = _name + "\\";
}
void DataMaker::setNumber(int _number)
{
	number = _number;
	method.resize(number + 1);
	for(int i = 0; i < method.size(); i++)
		method[i] = NULL;
}
void DataMaker::setStdName(string _stdName)
{
	stdName = _stdName;
}
void DataMaker::setMethod(int l, int r, void (*fun)(DataMaker&, int))
{
	if(l > r || l < 1 || r > number)
		error(string() + "setMethod(" + l + ", " + r + ")");
	for(int i = l; i <= r; i++)
		method[i] = fun;
}
void DataMaker::generate()
{
	if(name == "") error("Name is empty!");
	if(number <= 0) error("Number is invalid");
	
	system("mkdir " + dataDir);
	
	for(int i = 1; i <= number; i++)
	{
		inputFile = dataDir + name + i + ".in";
		outputFile = dataDir + name + i + ".out";	
		fin.open(inputFile.c_str());
		fout.open(outputFile.c_str());
		
		if(!fin) error("Can't open " + inputFile);
		if(!fout) error("Can't open " + outputFile);
		
		method[i](*this, i);
		
		fin.close();
		fout.close();
		
		if(stdName != "")
			runStd();
	}
	cout << "Succeed!" << endl;
}
void DataMaker::runStd()
{
	if(stdName == "") error("stdName id empty!");
	
	fin.close();
	fout.close();
	system(string() + stdName + " < " + inputFile + " > " + outputFile);
}

// rand extension
int rand(int l, int r)
{
	return (((rand() & 32767) << 15) | (rand() & 32767)) % (r - l + 1) + l;
}

//system extension
int system(const string &cmd)
{
	return system(cmd.c_str());
}

// overload string + int/double
string operator + (const string &s, const int &a)
{
	char tmp[10];
	sprintf(tmp, "%d", a);
	return s + tmp;
}
string operator + (const string &s, const double &a)
{
	char tmp[10];
	sprintf(tmp, "%lf", a);
	return s + tmp;
}

// throw an exception
void error(const string &err)
{
	cout << "Error encountered : " << err << endl;
	exit(1);
}



