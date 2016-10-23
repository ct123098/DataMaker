#ifndef DATAMAKER_DATAMAKER_H
#define DATAMAKER_DATAMAKER_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include <vector>
#include <string>

#include "functions.h"

using namespace std;

// DataMaker
typedef void(*CustomFunction)(int);

class DataMaker
{
public:
	
	DataMaker(string _name, int _lower, int _upper, string _stdName = "", string _forceName = "");
	
	~DataMaker();
	
	fstream &getFin();
	
	fstream &getFout();
	
	DataMaker &setTmpDir(string _name);
	
	DataMaker &setName(string _name);
	
	DataMaker &setBound(int _lower, int _upper);
	
	DataMaker &setStandardName(string _name);
	
	DataMaker &setForceName(string _name);
	
	DataMaker &setMethod(int l, int r, CustomFunction fun);
	
	DataMaker &setMethod(int x, CustomFunction fun);
	
	void runStandardProgram();
	
	void runForceProgram();
	
	void generate();

private:
	
	fstream fin;
	fstream fout;
	string problemName;
	int lowerBound, upperBound;
	string standardCodeName, forceCodeName, standardExecName, forceExecName;
	string dataDir, tmpDir, inputFile, outputFile;
	vector<CustomFunction> method;
};

#endif //DATAMAKER_DATAMAKER_H
