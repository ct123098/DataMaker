#ifndef DATAMAKER_DATAMAKER_H
#define DATAMAKER_DATAMAKER_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

#include "functions.h"

using namespace std;

// DataMaker
class DataMaker
{

public:
	fstream fin;
	fstream fout;
	
	DataMaker(string _name, int _number, string _stdName = "", string _forceName = "");
	
	DataMaker &setName(string _name);
	
	DataMaker &setNumber(int _number);
	
	DataMaker &setStandardName(string _name);
	
	DataMaker &setForceName(string _name);
	
	DataMaker &setMethod(int l, int r, void (*fun)(DataMaker &, int));
	
	void runStandardProgram();
	
	void runForceProgram();
	
	void generate();

private:
	string name;
	int number;
	string standardName, forceName;
	string dataDir, inputFile, outputFile;
	vector<void (*)(DataMaker &, int)> method;
};

#endif //DATAMAKER_DATAMAKER_H
