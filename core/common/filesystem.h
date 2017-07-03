//
// Created by chentong on 17-7-3.
//

#ifndef DATAMAKER_FILESYSTEM_H
#define DATAMAKER_FILESYSTEM_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "functions.h"

namespace datamaker
{
//	extern const string OS;
//	extern const string SEP;

//	extern string getOS();
//
//	extern string getPathSeparator();

	extern bool compile(const string &source, const string &exec, const string &par = "");

	extern bool execute(const string &exec, const string &par = "");

	extern bool create_directory(const string &name);

	extern bool remove_directory(const string &name);

	extern bool remove_file(const string &name);

//	extern string redirect_input(const string &name);
//
//	extern string redirect_output(const string &name);

	extern bool has_file(const string &name);

//	extern string fileExist(const string file);
//
//	extern string fileNotExist(const string file);
//
//	extern string selectionIf(const string &condition, const string statement);
//
//	extern string selectionElse(const string &condition, const string statement);
//
//	extern string selectionIfElse(const string &condition, const string statement1, const string statement2);
}


#endif //DATAMAKER_FILESYSTEM_H
