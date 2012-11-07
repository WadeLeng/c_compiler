#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <vector>
#include <string>
using namespace std;

class Production
{
public:
	Production();
	int get_index_of(string element);
	vector<string> p_list;
};

#endif
