//
// Created by chentong on 17-7-3.
//

#ifndef DATAMAKER_DATAMAKER_H
#define DATAMAKER_DATAMAKER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <map>

#include "common/functions.h"
#include "common/filesystem.h"
#include "jsoncpp/include/json/json.h"

namespace datamaker
{
	using namespace std;

	typedef void(*method)(void);

	struct Info
	{
		string problem_name;
		string solver_dir, data_dir, tmp_dir;
		string standard_code, standard_prog;

		struct Group
		{
			vector<int> index;
			string function;

			struct Parameter
			{
				vector<int> id, par;

				Parameter();

				Parameter(Json::Value json_val);
			};

			vector <Parameter> parameters;

			Group();

			Group(Json::Value json_val);
		};

		vector <Group> groups;

		vector<int> index;

		map <string, method> str_to_func;
		map<int, vector<int> > id_to_par;
		map<int, method> id_to_func;

		int cur_id;
		string cur_input_str, cur_output_str;

		Info();

		Info(Json::Value json_val);
	};

	extern Info info;

	extern fstream input;
	extern fstream output;

	extern void init();

	extern void bind(const string &name, method func);

	extern void run();

	extern void clear();

	extern void run_standard();
}


#endif //DATAMAKER_DATAMAKER_H
