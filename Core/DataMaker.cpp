#include "DataMaker.h"

using namespace std;

// DataMaker
DataMaker::DataMaker()
{
	srand(time(0));
	clear();

	setName("problem");
	setTmpDir("Tmp");
}

DataMaker::~DataMaker()
{
	cleanup();
}

void DataMaker::clear()
{
	fin.clear();
	fout.clear();
	inputFile = outputFile = "";

	problemName = "";
	standardCodeName = standardExecName = "";
	forceCodeName = forceExecName = "";
	dataDir = tmpDir = "";

	method.clear();
}

void DataMaker::cleanup()
{
	system(removeDirectory(tmpDir));
}

void DataMaker::info()
{
	cout << "*** INFO ***" << endl;
	cout << "Name : " << problemName << endl;
	cout << endl;
	cout << "Data Directory : " << dataDir << endl;
	cout << "Temporary DIrectory : " << tmpDir << endl;
	cout << endl;
	cout << "Standard Code Name : " << (standardCodeName.empty() ? "Not set" : standardCodeName) << endl;
	cout << "Standard Executable File Name : " << (standardExecName.empty() ? "Not set" : standardExecName) << endl;
	cout << "Brute Force Code Name : " << (forceCodeName.empty() ? "Not set" : forceCodeName) << endl;
	cout << "Brute Force Executable File Name : " << (forceExecName.empty() ? "Not set" : forceExecName) << endl;
	cout << endl;
	cout << "Data Number : ";
	for(map<int, CustomFunctionPointer>::iterator it = method.begin(); it != method.end(); it++)
		cout << it->first << ' ';
	cout << endl;
	cout << "*** INFO END ***" << endl;
	cout << "Please press ENTER to continue... ";
	getchar();
}

fstream &DataMaker::getFin()
{
	return fin;
}

fstream &DataMaker::getFout()
{
	return fout;
}

DataMaker &DataMaker::setName(string _name)
{
	problemName = _name;
	setDataDir(problemName);
	return *this;
}

DataMaker &DataMaker::setDataDir(string _name)
{
	dataDir = _name + SEP;
	return *this;
}

DataMaker &DataMaker::setTmpDir(string _name)
{
	tmpDir = _name + SEP;
	return *this;
}

DataMaker &DataMaker::setStandardCodeName(string _name)
{
	standardCodeName = _name;
	standardExecName = tmpDir + "standard";
	return *this;
}

DataMaker &DataMaker::setForceCodeName(string _name)
{
	forceCodeName = _name;
	forceExecName = tmpDir + "force";
	return *this;
}

DataMaker &DataMaker::setMethod(int l, int r, CustomFunctionPointer fun)
{
	if(l > r)
		error("setMethod() : l, r is invalid");
	for(int i = l; i <= r; i++)
		method[i] = fun;
	return *this;
}

DataMaker &DataMaker::setMethod(int x, CustomFunctionPointer fun)
{
	setMethod(x, x, fun);
	return *this;
}

void DataMaker::makeDataDir()
{
	string cmd = selectionIf(fileNotExist(dataDir), makeDirectory(dataDir));
	if(system(cmd))
		error(string() + "Can't make data directory! " + "(" + cmd + ")");

}

void DataMaker::makeTmpDir()
{
	string cmd = selectionIf(fileNotExist(tmpDir), makeDirectory(tmpDir));
	if(system(cmd))
		error(string() + "Can't make temporary directory! " + "(" + cmd + ")");
}

void DataMaker::compileStandardCode()
{
	string cmd = compile(standardCodeName, standardExecName);
	if(system(cmd))
		error(string() + "Error occured when compiling standard code! "
			  + "(" + cmd + ")");
}

void DataMaker::compileForceCode()
{
	string cmd = compile(forceCodeName, forceExecName);
	if(system(cmd))
		error(string() + "Error occured when compiling force code! "
			  + "(" + cmd + ")");
}

void DataMaker::generate()
{
	info();

	makeDataDir();
	makeTmpDir();
	if(!standardCodeName.empty()) compileStandardCode();
	if(!forceCodeName.empty()) compileForceCode();

	for(map<int, CustomFunctionPointer>::iterator it = method.begin(); it != method.end(); it++)
	{
		int id = it->first;
		CustomFunctionPointer fun = it->second;

		inputFile = dataDir + problemName + id + ".in";
		outputFile = dataDir + problemName + id + ".out";

		cout << "Running Case#" << id << " (" + inputFile + ", " + outputFile + ") " + " : " << endl;

		fin.open(inputFile.c_str(), ios::out);
		fout.open(outputFile.c_str(), ios::out);

		if(!fin) error("Can't open " + inputFile);
		if(!fout) error("Can't open " + outputFile);

		fun(id);

		fin.close();
		fout.close();
	}
	cout << "Succeed!" << endl;
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
		error(string() + "can't run standard program " + "(" + cmd + ")");

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
		error(string() + "can't run force program " + "(" + cmd + ")");

	fin.open(inputFile.c_str(), ios::out | ios::app);
	fout.open(outputFile.c_str(), ios::out | ios::app);
}
