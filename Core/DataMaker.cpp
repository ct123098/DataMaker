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
	srand(time(0));
	
	fin.clear();
	fout.clear();
	inputFile = outputFile = "";
	
	setTmpDir("Tmp");
	setName(_name);
	setBound(_lower, _upper);
	
	if(!_stdName.empty()) setStandardName(_stdName);
	if(!_forceName.empty()) setForceName(_forceName);
}

DataMaker::~DataMaker()
{
	system(removeDirectory(tmpDir));
}


fstream &DataMaker::getFin()
{
	return fin;
}

fstream &DataMaker::getFout()
{
	return fout;
}

DataMaker &DataMaker::setTmpDir(string _name)
{
	tmpDir = _name + SEP;
	system(makeDirectory(tmpDir));
	return *this;
}

DataMaker &DataMaker::setName(string _name)
{
	problemName = _name;
	dataDir = problemName + SEP;
	system(makeDirectory(dataDir));
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

DataMaker &DataMaker::setStandardName(string _name)
{
	standardCodeName = _name;
	standardExecName = tmpDir + "standard";
	string cmd = compile(standardCodeName, standardExecName);
	if(system(cmd))
		error(string() + "Error occured when compiling standard code! "
			  + "Running command : " + cmd);
	return *this;
}

DataMaker &DataMaker::setForceName(string _name)
{
	forceCodeName = _name;
	forceExecName = tmpDir + "force";
	string cmd = compile(forceCodeName, forceExecName);
	if(system(cmd))
		error(string() + "Error occured when compiling force code! "
			  + "Running command : " + cmd);
	return *this;
}

DataMaker &DataMaker::setMethod(int l, int r, CustomFunction fun)
{
	if(l > r || l < lowerBound || r > upperBound)
		error("setMethod() : l, r is invalid");
	for(int i = l; i <= r; i++)
		method[i - lowerBound] = fun;
	return *this;
}

DataMaker &DataMaker::setMethod(int x, CustomFunction fun)
{
	return setMethod(x, x, fun);
}

void DataMaker::runStandardProgram()
{
	if(standardExecName == "") error("standardName id empty!");
	if(inputFile == "") error("no input file");
	if(outputFile == "") error("no output file");
	
	fin.close();
	fout.close();
	
	string cmd = run(standardExecName) + redirectInput(inputFile) + redirectOutput(outputFile);
	if(system(cmd))
		error("can't run standard program");
	
	fin.open(inputFile.c_str(), ios::out | ios::app);
	fout.open(outputFile.c_str(), ios::out | ios::app);
}

void DataMaker::runForceProgram()
{
	if(forceExecName == "") error("forceName is empty!");
	if(inputFile == "") error("no input file");
	if(outputFile == "") error("no output file");
	
	fin.close();
	fout.close();
	
	string cmd = run(forceExecName) + redirectInput(inputFile) + redirectOutput(outputFile);
	if(system(cmd))
		error("can't run force program");
	
	fin.open(inputFile.c_str(), ios::out | ios::app);
	fout.open(outputFile.c_str(), ios::out | ios::app);
}

void DataMaker::generate()
{
	if(problemName == "") error("Name is empty!");
	if(upperBound < lowerBound) error("Number is invalid");
	
	for(int i = lowerBound; i <= upperBound; i++)
	{
		inputFile = dataDir + problemName + i + ".in";
		outputFile = dataDir + problemName + i + ".out";
		
		cout << "Running Case#" << i << " (" + inputFile + ", " + outputFile + ") " + " : " << endl;
		
		fin.open(inputFile.c_str(), ios::out);
		fout.open(outputFile.c_str(), ios::out);
		
		if(!fin) error("Can't open " + inputFile);
		if(!fout) error("Can't open " + outputFile);
		
		method[i - lowerBound](i);
		
		fin.close();
		fout.close();
	}
	cout << "Succeed!" << endl;
}