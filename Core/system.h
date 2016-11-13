#ifndef DATAMAKER_SYSTEM_H
#define DATAMAKER_SYSTEM_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>

using namespace std;


extern const string OS;
extern const string SEP;

extern string getOS();

extern string getPathSeparator();

extern string compile(const string &source, const string &exec);

extern string run(const string &exec);

extern string makeDirectory(const string &name);

extern string removeDirectory(const string &name);

extern string removeFile(const string &name);

extern string redirectInput(const string &name);

extern string redirectOutput(const string &name);

extern string fileExist(const string file);

extern string fileNotExist(const string file);

extern string selectionIf(const string &condition, const string statement);

extern string selectionElse(const string &condition, const string statement);

extern string selectionIfElse(const string &condition, const string statement1, const string statement2);


#endif //DATAMAKER_SYSTEM_H
