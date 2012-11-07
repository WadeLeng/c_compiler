#include <cstdio>
#include "parser.h"
#include "expression.h"

void Expression::merge(vector<string> &merge_code)
{
	code.insert(code.end(), merge_code.begin(), merge_code.end());
}

void Expression::generation(int label, string jmp)
{
	string tl;

	tl = Parser::int_to_string(label);
	while_start = string("while_start") + tl + string(":");
	while_jmp_fail = jmp + string(" while_fail") + tl;
	while_jmp_start = string("jmp while_start") + tl;
	while_fail = string("while_fail") + tl + string(":");
	if_start = jmp + string(" if_fail") + tl;
	if_jmp_selection_end = string("jmp if_selection_end") + tl;
	if_fail = string("if_fail") + tl + string(":");
	if_selection_end = string("if_selection_end") + tl + string(":");
}
