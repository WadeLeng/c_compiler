#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <vector>
#include "production.h"
#include "expression.h"
#include "lexical.h"
#include "table.h"
#include "token.h"
#include "symbol.h"

class Parser
{
public:
	Parser(vector<Token> &token_list);
	void anylize();
	void syntax_directed(string reduce);
	void print_action_table();
	void print_goto_table();
	void print_reduce_list();

	vector<string> text_msg;
	vector<Symbol> symbol_table;
	stack<Expression> code_stack;
	vector<string> reduce_list;
	static string int_to_string(int num);
private:
	Token* get_stack_of(int num);
	string find_address(string value);
	int get_index(string *index, string target);
	int get_shift_state(string element);
	string get_reduce_state(string element, int &pop_number);

	int baseAddr;
	int symbol_table_index;
	int text_label;
	int code_label;
	Table tab;
	stack<Token> token_stack;
	stack<int> state_stack;
	vector<Token> token_list;
	Production production;
};

#endif
