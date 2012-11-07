
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <vector>
using namespace std;

class Expression
{
public:
	void merge(vector<string> &merge_code);
	void generation(int label, string jmp);

	vector<string> code;
	string while_start;
	string while_jmp_fail;
	string while_jmp_start;
	string while_fail;
	string if_start;
	string if_selection_end;
	string if_fail;
	string if_jmp_selection_end;
};

#endif
