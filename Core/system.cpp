#include "functions.h"
#include "system.h"


const string OS = getOS();
const string SEP = getPathSeparator();

string getOS()
{
#ifdef _WIN32
	return "Windows";
#elif linux
	return "Linux";
#else
	error("Can't recognize which OS it is!");
#endif
}

string getPathSeparator()
{
#ifdef _WIN32
	return "\\";
#elif linux
	return "/";
#else
	error("Can't recognize which OS it is!");
#endif
}

string compile(const string &source, const string &exec)
{
#ifdef _WIN32
	return string() + "g++ " + source + " " + "-o " + exec;
#elif linux
	return string() + "g++ " + source + " " + "-o " + exec;
#else
	error("Can't recognize which OS it is!");
#endif
}

string run(const string &exec)
{
#ifdef _WIN32
	return string() + exec;
#elif linux
	return string() + "./" + exec;
#else
	error("Can't recognize which OS it is!");
#endif
}

string makeDirectory(const string &name)
{
#ifdef _WIN32
	return string() + "mkdir " + name;
#elif linux
	return string() + "mkdir " + name;
#else
	error("Can't recognize which OS it is!");
#endif
}

string removeDirectory(const string &name)
{
#ifdef _WIN32
	return string() + "rmdir " + name + " " + "/s /q";
#elif linux
	return string() + "rm " + name + " " + "-r -f";
#else
	error("Can't recognize which OS it is!");
#endif
}

string removeFile(const string &name)
{
#ifdef _WIN32
	return string() + "del " + name;
#elif linux
	return string() + "rm " + name + " " + "-f";
#else
	error("Can't recognize which OS it is!");
#endif
}

string redirectInput(const string &name)
{
#ifdef _WIN32
	return string() + " < " + name;
#elif linux
	return string() + " < " + name;
#else
	error("Can't recognize which OS it is!");
#endif
}

string redirectOutput(const string &name)
{
#ifdef _WIN32
	return string() + " > " + name;
#elif linux
	return string() + " > " + name;
#else
	error("Can't recognize which OS it is!");
#endif
}

string fileExist(const string file)
{
#ifdef _WIN32
	return string() + " exist " + "\"" + file + "\"";
#elif linux
	return string() + " -f " + "\"" + file + "\"";
#else
	error("Can't recognize which OS it is!");
#endif
}

string fileNotExist(const string file)
{
#ifdef _WIN32
	return string() + " not exist " + "\"" + file + "\"";
#elif linux
	return string() + " ! -d " + "\"" + file + "\"";
#else
	error("Can't recognize which OS it is!");
#endif
}

string directoryNotExist(const string file)
{
#ifdef _WIN32
	return string() + " not exist " + "\"" + file + "\"";
#elif linux
	return string() + " ! -d " + "\"" + file + "\"";
#else
	error("Can't recognize which OS it is!");
#endif
}

string selectionIf(const string &condition, const string statement)
{
#ifdef _WIN32
	return string() + "if " + condition + " (" + statement + ")";
#elif linux
	return string() + "if [ " + condition + " ]; then\n" + statement + "\nfi\n";
#else
	error("Can't recognize which OS it is!");
#endif
}

string selectionElse(const string &condition, const string statement)
{
#ifdef _WIN32
	return string() + "if " + condition + " else " + "(" + statement + ")";
#elif linux
	return string() + "if [ " + condition + " ]; then\n" + "else\n" + statement + "\nfi\n";
#else
	error("Can't recognize which OS it is!");
#endif
}

string selectionIfElse(const string &condition, const string statement1, const string statement2)
{
#ifdef _WIN32
	return string() + "if " + condition + " (" + statement1 + ") " + "else " + "(" + statement2 + ")";
#elif linux
	return string() + "if [ " + condition + " ]; then\n" + statement1 + "\nelse\n" + statement2 + "\nfi\n";
#else
	error("Can't recognize which OS it is!");
#endif
}
