#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "core/datamaker.h"
#include "core/load_cpp.inc"

using namespace std;

void fun1()
{
	using namespace datamaker;
	int id, a, b;
	cin >> id >> a >> b;
	cout << a << ' ' << b << endl;
	input << a << ' ' << b << endl;
	output << a + b << endl;
}
void fun2()
{
	using namespace datamaker;
	int id, a, b;
	cin >> id >> a >> b;
	a += rand_range(-10, 10), b += rand_range(-100, 100);
	cout << a << ' ' << b << endl;
	input << a << ' ' << b << endl;
	run_standard();
}

int main()
{
	ios::sync_with_stdio(false);

	datamaker::init();
	datamaker::bind("fun1", fun1);
	datamaker::bind("fun2", fun2);
	datamaker::run();
	datamaker::clean();
	
	return 0;
}
