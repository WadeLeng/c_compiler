#include "symbol.h"
using namespace std;

Symbol::Symbol()
{
}

Symbol::Symbol(string type, string value, vector<string> &some_variables, 
		int size, int address, vector<int> &array_value, bool is_array)
{
	this->type = type;
	this->value = value;
	this->address = address;
	this->size = size;
	this->is_array = is_array;
	this->some_variables.assign(some_variables.begin(), some_variables.end());
	this->array_value.assign(array_value.begin(), array_value.end());
}
