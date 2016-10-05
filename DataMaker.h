#include <fstream>
#include <vector>
#include <string>

using namespace std;

// DataMaker
class DataMaker
{

public:
	
	ofstream fin;
	ofstream fout;
	
	DataMaker(string _name, int _number, string _stdName = "");
	
	void setName(string _name);
	void setNumber(int _number);
	void setStdName(string _stdName);
	void setMethod(int l, int r, void (*fun)(DataMaker&, int));
	
	void generate();

private:
	string name;
	string stdName;
	string dataDir, inputFile, outputFile;
	int number;
	vector<void (*)(DataMaker&, int)> method;
	
	void runStd();

};

// rand extension
int rand(int l, int r);

//system extension
int system(const string &cmd);

// overload string + int/double
string operator + (const string &s, const int &a);
string operator + (const string &s, const double &a);

// throw an exception
void error(const string &err);


