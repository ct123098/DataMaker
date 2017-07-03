//
// Created by chentong on 17-7-3.
//

#include "filesystem.h"

namespace datamaker
{
#ifdef linux
	bool compile(const string &source, const string &exec, const string &par)
	{
		return xsystem("g++ " +  source + " -o " + exec + "  " + par);
	}
	bool run(const string &exec)
	{
		return xsystem("./" + exec);
	}
	bool create_directory(const string &name)
	{
		return xsystem("mkdir " + name);
	}
	bool remove_directory(const string &name)
	{
		return xsystem("rm " + name + " -rf ");
	}
	bool remove_file(const string &name)
	{
		return xsystem("rm " + name + " -f ");
	}
#elif _WIN32
	bool compile(const string &source, const string &exec, const string &par)
	{
		return xsystem("g++ " +  source + " -o " + exec + "  " + par);
	}
	bool run(const string &exec)
	{
		return xsystem(exec);
	}
	bool create_directory(const string &name)
	{
		return xsystem("mkdir " + name);
	}
	bool remove_directory(const string &name)
	{
		return xsystem("rmdir " + name + " /s /q ");
	}
	bool remove_file(const string &name)
	{
		return xsystem("del " + name);
	}
#else

#endif
}
