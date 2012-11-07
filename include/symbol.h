#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
using namespace std;

class Symbol
{
public:
	Symbol();
	Symbol(string type, string value, vector<string> &some_variables, 
			int size, int address, vector<int> &array_value, bool is_array);

	string type;
	string value;
	int address;
	int size;
	vector<string> some_variables;
	vector<int> array_value;
	bool is_array;
};

#endif
