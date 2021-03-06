#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "core/datamaker.h"
#include "core/load_cpp.inc"

using namespace std;

bool gen1()
{
	using namespace datamaker;
	int id, a, b;
	cin >> id >> a >> b;
	cout << a << ' ' << b << endl;
	input << a << ' ' << b << endl;
	output << a + b << endl;
	return true;
}
bool gen2()
{
	using namespace datamaker;
	int id, a, b;
	cin >> id >> a >> b;
	a += rand_range(-10, 10), b += rand_range(-100, 100);
	cout << a << ' ' << b << endl;
	input << a << ' ' << b << endl;
	return run_standard();
}

bool chk2()
{
	using namespace datamaker;
	int id, a, b, x, y;
	cin >> id >> a >> b;
	input >> x >> y;
	cout << a << ' ' << b << ' ' << x << ' ' << y << endl;
	return x + y > a + b;
}

int main()
{
	ios::sync_with_stdio(false);

	datamaker::init();
	datamaker::bind("gen1", gen1);
	datamaker::bind("gen2", gen2);
	datamaker::bind("chk2", chk2);
	datamaker::run();
	datamaker::clean();
	
	return 0;
}

