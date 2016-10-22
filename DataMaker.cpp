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

DataMaker &DataMaker::setTmpDir(string _name)
{
	tmpDir = _name + getPathSeparator();
	system(removeDirectory(tmpDir));
	system(makeDirectory(tmpDir));
	return *this;
}

DataMaker &DataMaker::setName(string _name)
{
	name = _name;
	dataDir = name + getPathSeparator();
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
	standardName = _name;
	if(system(compile(standardName, tmpDir + "standard")))
		error(string() + "Error occured when compiling standard code! "
			  + "Running command : "
			  + compile(standardName, tmpDir + "standard"));
	return *this;
}

DataMaker &DataMaker::setForceName(string _name)
{
	forceName = _name;
	if(system(compile(forceName, tmpDir + "force")))
		error(string() + "Error occured when compiling force code! "
			  + "Running command : "
			  + compile(forceName, tmpDir + "force"));
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


DataMaker &DataMaker::setMethod(int x, void (*fun)(DataMaker &, int))
{
	return setMethod(x, x, fun);
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
	if(system(run(tmpDir + "standard")
			  + redirectInput(inputFile)
			  + redirectOutput(outputFile)))
		error("can't run standard program");
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
	if(system(run(tmpDir + "force")
			  + redirectInput(inputFile)
			  + redirectOutput(outputFile)))
		error("can't run force program");
	fin.open(inputFile.c_str(), ios::app);
	fout.open(outputFile.c_str(), ios::app);
}

void DataMaker::generate()
{
	if(name == "") error("Name is empty!");
	if(upperBound < lowerBound) error("Number is invalid");
	
	for(int i = lowerBound; i <= upperBound; i++)
	{
		inputFile = dataDir + name + i + ".in";
		outputFile = dataDir + name + i + ".out";
		
		cout << "Running Case#" << i << " (" + inputFile + ", " + outputFile + ") " + " : " << endl;
		
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