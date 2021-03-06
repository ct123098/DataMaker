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
		for(int i = 0; i < json_val["generating_method"].size(); i++)
			groups.push_back(Group(json_val["generating_method"][i]));
	}

	Info::Group::Group()
	{}
	Info::Group::Group(Json::Value json_val)
	{
		for(int i = 0; i < json_val["index"].size(); i++)
			index.push_back(json_val["index"][i].asInt());
		gen_func = json_val.get("gen_func", "").asString();
		chk_func = json_val.get("chk_func", "").asString();
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
				info.id_to_gen[info.groups[i].index[j]] = info.str_to_func[info.groups[i].gen_func];
				info.id_to_chk[info.groups[i].index[j]] = info.str_to_func[info.groups[i].chk_func];
			}
		for(int i = 0; i < info.groups.size(); i++)
			for(int j = 0; j < info.groups[i].parameters.size(); j++)
				for(int k = 0; k < info.groups[i].parameters[j].id.size(); k++)
					info.id_to_par[info.groups[i].parameters[j].id[k]] = info.groups[i].parameters[j].par;

		create_directory(info.tmp_dir);
		create_directory(info.data_dir);
		sleep("1s");

		if(info.standard_code != "")
		{
			info.standard_code = info.solver_dir + info.standard_code;
			info.standard_prog = info.tmp_dir + "std";
			compile(info.standard_code, info.standard_prog, "");
		}

		for(int t = 0; t < info.index.size(); t++)
		{
			int id = info.index[t];
			info.cur_id = id;

			cout << "Generating case " << id << "... " << endl;

			info.cur_input_str = info.data_dir + info.problem_name + id + ".in";
			input.open(info.cur_input_str, ios::out);
			xassert(input.is_open(), "can't open data input file");

			info.cur_output_str = info.data_dir + info.problem_name + id + ".out";
			output.open(info.cur_output_str, ios::out);
			xassert(output.is_open(), "can't open data output file");

			method gen_func = info.id_to_gen[id];
			method chk_func = info.id_to_chk[id];
			
			xassert(gen_func, "");
			
			vector<int> vec = info.id_to_par[id];
			stringstream ss;
			ss.clear();
			ss << id << endl;
			for(int i = 0; i < vec.size(); i++)
				ss << vec[i] << ' ';
			cin.rdbuf(ss.rdbuf());
			
			bool flag = gen_func();
			
			input.close();
			output.close();
			
			if(!flag)
			{
				cout << "Failed" << endl;
				cout << endl;
				t--; continue;
			}


			/*** check valid ***/
			if(chk_func)
			{
				input.open(info.cur_input_str, ios::in);
				output.open(info.cur_output_str, ios::in);
				
				vector<int> vec = info.id_to_par[id];
				stringstream ss;
				ss.clear();
				ss << id << endl;
				for(int i = 0; i < vec.size(); i++)
					ss << vec[i] << ' ';
				cin.rdbuf(ss.rdbuf());
				
				bool flag = chk_func();
				
				input.close();
				output.close();
				
				if(!flag)
				{
					cout << "Failed" << endl;
					cout << endl;
					t--; continue;
				}
			}

			cout << "Finished" << endl;
			cout << endl;
		}
	}

	void clean()
	{
		remove_directory(info.tmp_dir);
	}

	bool run_standard()
	{
		input.close();
		output.close();
		bool ret = execute(info.standard_prog, " < " + info.cur_input_str + " > " + info.cur_output_str);
		input.open(info.cur_input_str, ios::out | ios::app);
		output.open(info.cur_output_str, ios::out | ios::app);
		return ret;
	}
}

