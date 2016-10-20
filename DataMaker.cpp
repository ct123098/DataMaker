#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>

#include "DataMaker.h"

using namespace std;

// DataMaker
DataMaker::DataMaker(string _name, int _lower, int _upper, string _stdName, string _forceName)
{
	setName(_name);
	setBound(_lower, _upper);

	if(!_stdName.empty()) setStandardName(_stdName);
	if(!_forceName.empty()) setForceName(_forceName);

	fin.clear();
	fout.clear();
	inputFile = outputFile = "";

	srand(time(0));
}

DataMaker &DataMaker::setName(string _name)
{
	name = _name;
	dataDir = _name + "/";
	return *this;
}

DataMaker &DataMaker::setBound(int _lower, int _upper)
{
	lowerBound = _lower;
	upperBound = _upper;
	method.resize(upperBound - lowerBound + 1);
	for(int i = 0; i < method.size(); i++)
		method[i] = NULL;
	return *this;
}

DataMaker &DataMaker::DataMaker::setStandardName(string _name)
{
	standardName = _name;
	int res = system("g++ " + standardName + " " + "-o " + "standard");
	if(res != 0)
		error("Error occured when compiling standard code!");
	return *this;
}

DataMaker &DataMaker::setForceName(string _name)
{
	forceName = _name;
	int res = system("g++ " + forceName + " " + "-o " + "force");
	if(res != 0)
		error("Error occured when compiling force code!");
	return *this;
}

DataMaker &DataMaker::setMethod(int l, int r, void (*fun)(DataMaker &, int))
{
	if(l > r || l < lowerBound || r > upperBound)
		error("setMethod() : l, r is invalid");
	for(int i = l; i <= r; i++)
		method[i - lowerBound] = fun;
	return *this;
}

void DataMaker::runStandardProgram()
{
	if(standardName == "")
		error("standardName id empty!");
	if(inputFile == "")
		error("no input file");
	if(outputFile == "")
		error("no output file");

	fin.close();
	fout.close();
	system(string() + "./standard" + " < " + inputFile + " > " + outputFile);
	fin.open(inputFile.c_str(), ios::app);
	fout.open(outputFile.c_str(), ios::app);
}

void DataMaker::runForceProgram()
{
	if(forceName == "")
		error("forceName is empty!");
	if(inputFile == "")
		error("no input file");
	if(outputFile == "")
		error("no output file");

	fin.close();
	fout.close();
	system(string() + "./force" + " < " + inputFile + " > " + outputFile);
	fin.open(inputFile.c_str(), ios::app);
	fout.open(outputFile.c_str(), ios::app);
}

void DataMaker::generate()
{
	if(name == "") error("Name is empty!");
	if(upperBound < lowerBound) error("Number is invalid");

	system("mkdir " + dataDir);

	for(int i = lowerBound; i <= upperBound; i++)
	{
		cout << "Running Case#" << i << " : " << endl;
		inputFile = dataDir + name + i + ".in";
		outputFile = dataDir + name + i + ".out";
		fin.open(inputFile.c_str(), ios::out);
		fout.open(outputFile.c_str(), ios::out);

		if(!fin) error("Can't open " + inputFile);
		if(!fout) error("Can't open " + outputFile);

		method[i - lowerBound](*this, i);

		fin.close();
		fout.close();
	}
	cout << "Succeed!" << endl;
}