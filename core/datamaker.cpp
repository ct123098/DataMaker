//
// Created by chentong on 17-7-3.
//

#include "datamaker.h"

namespace datamaker
{
	Info::Info()
	{}
	Info::Info(Json::Value json_val)
	{
		problem_name = json_val.get("problem_name", "").asString();
		solver_dir = json_val.get("solver_dir", "./").asString();
		data_dir = json_val.get("data_dir", "./data/").asString();
		tmp_dir = json_val.get("tmp_dir", "./tmp/").asString();
		standard_code = json_val.get("standard_code", "std.cpp").asString();
		force_code = json_val.get("force_code", "force.cpp").asString();
		for(int i = 0; i < json_val["generating_method"].size(); i++)
			groups.push_back(Group(json_val["generating_method"][i]));
	}

	Info::Group::Group()
	{}
	Info::Group::Group(Json::Value json_val)
	{
		for(int i = 0; i < json_val["index"].size(); i++)
			index.push_back(json_val["index"][i].asInt());
		function = json_val.get("function", "").asString();
		for(int i = 0; i < json_val["parameter"].size(); i++)
			parameters.push_back(Parameter(json_val["parameter"][i]));
	}

	Info::Group::Parameter::Parameter()
	{}
	Info::Group::Parameter::Parameter(Json::Value json_val)
	{
		for(int i = 0; i < json_val["id"].size(); i++)
			id.push_back(json_val["id"][i].asInt());
		for(int i = 0; i < json_val["par"].size(); i++)
			par.push_back(json_val["par"][i].asInt());
	}
}

namespace datamaker
{
	Info info;
	fstream input;
	fstream output;

	void init()
	{
		// load settings
		ifstream setting_file("settings.json");
		xassert(setting_file.is_open(), "can't open settings.json file");

		Json::Value root;
		setting_file >> root;
		info = root;
		// finished
	}

	void bind(const string &name, method func)
	{
		xassert(info.str_to_func.find(name) == info.str_to_func.end(),
				"redefined same function name");
		info.str_to_func[name] = func;
	}

	void run()
	{
		// processing numbers
		for(int i = 0; i < info.groups.size(); i++)
			for(int j = 0; j < info.groups[i].index.size(); j++)
			{
				info.index.push_back(info.groups[i].index[j]);
				info.id_to_func[info.groups[i].index[j]] = info.str_to_func[info.groups[i].function];
			}
		for(int i = 0; i < info.groups.size(); i++)
			for(int j = 0; j < info.groups[i].parameters.size(); j++)
				for(int k = 0; k < info.groups[i].parameters[j].id.size(); k++)
					info.id_to_par[info.groups[i].parameters[j].id[k]] = info.groups[i].parameters[j].par;

		create_directory(info.tmp_dir);
		create_directory(info.data_dir);

		if(info.standard_code != "")
		{
			info.standard_code = info.solver_dir + info.standard_code;
			info.standard_prog = info.tmp_dir + "std";
			compile(info.standard_code, info.standard_prog, "");
		}
		if(info.force_code != "")
		{
			info.force_code = info.solver_dir + info.force_code;
			info.force_prog = info.tmp_dir + "force";
			compile(info.force_code, info.force_prog, "");
		}

		for(int t = 0; t < info.index.size(); t++)
		{
			int id = info.index[t];
			cout << "Generating case" << id << "... " << endl;
			input.open(info.data_dir + info.problem_name + id + ".in", ios::out);
			xassert(input.is_open(), "can't open data input file");

			output.open(info.data_dir + info.problem_name + id + ".out", ios::out);
			xassert(output.is_open(), "can't open data output file");

			method func = info.id_to_func[id];
			vector<int> vec = info.id_to_par[id];
			stringstream ss;
			ss << id << endl;
			for(int i = 0; i < vec.size(); i++)
				ss << vec[i] << ' ';
			cin.rdbuf(ss.rdbuf());

			func();

			input.close();
			output.close();
			cout << "Finished" << endl;
		}
	}

	void clean()
	{
		remove_directory(info.tmp_dir);
	}
}
