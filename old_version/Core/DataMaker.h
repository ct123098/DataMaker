#ifndef DATAMAKER_DATAMAKER_H
#define DATAMAKER_DATAMAKER_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include <ctime>

#include <string>
#include <vector>
#include <map>
#include <set>

#include "functions/system.h"
#include "functions/functions.h"

using namespace std;

// DataMaker
typedef void(*CustomFunctionPointer)(int);

class DataMaker
{
public:

	DataMaker();

	~DataMaker();


	void clear();

	void cleanup();

	void info();


	fstream &getInFstream();

	fstream &getOutFstream();


	DataMaker &setName(string _name);

	DataMaker &setTmpDir(string _name);

	DataMaker &setDataDir(string _name);

	DataMaker &setStandardCodeName(string _name);

	DataMaker &setForceCodeName(string _name);

	DataMaker &setMethod(int l, int r, CustomFunctionPointer fun);

	DataMaker &setMethod(int x, CustomFunctionPointer fun);


	void makeTmpDir();

	void makeDataDir();

	void compileStandardCode();

	void compileForceCode();

	void runStandardProgram();

	void runForceProgram();


	void generate();

private:

	fstream fin, fout;
	string inputFile, outputFile;

	string problemName;
	string standardCodeName, forceCodeName, standardExecName, forceExecName;
	string dataDir, tmpDir;
	map<int, CustomFunctionPointer> method;
};

#endif //DATAMAKER_DATAMAKER_H
