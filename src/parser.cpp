#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "parser.h"
using namespace std;

Parser::Parser(vector<Token> &token_list)
{
	baseAddr = 0;
	symbol_table_index = 0;
	text_label = 1;
	code_label = 1;
	this->token_list.assign(token_list.begin(), token_list.end());
	state_stack.push(0);
}

void Parser::anylize()
{
	int index = 0;
	bool is_reduce = false;
	Token goto_token("", "");

	while (true)
	{
		if (!is_reduce)		//ACTION TABLE
		{
			Token current_token = token_list[index];
			int act_index = get_index(tab.action_index, current_token.type);
			string element = tab.action_table[state_stack.top()][act_index];

			if (element[0] == 's')			//shift
			{
				int to_state = get_shift_state(element);

				state_stack.push(to_state);
				token_stack.push(current_token);
				index++;
			}
			else if (element[0] == 'r')		//reduce
			{
				int pop_number = 0;
				string to_type;
				
				to_type = get_reduce_state(element, pop_number);
				syntax_directed(element);
				for (int i = 0; i < pop_number; i++)
				{
					state_stack.pop();
					token_stack.pop();
				}
				goto_token.type = to_type;
				goto_token.value = "";
				is_reduce = true;
				//cout << element << endl;
				reduce_list.push_back(element);

			}
			else if (element[0] == 'a')		//accept
			{
				break;
			}
			else							//error
			{
				cout << "find an error!" << endl;
				return;
			}
		}
		else				//GOTO TABLE
		{
			int current_state = state_stack.top();
			int go_index = get_index(tab.goto_index, goto_token.type);
			string element = tab.goto_table[current_state][go_index];

			state_stack.push(atoi(element.c_str()));
			token_stack.push(goto_token);
			is_reduce = false;
			//cout << "shift " << element << " (" << goto_token.type << ")" << endl;
		}
	}
	code_stack.pop();
}

int Parser::get_shift_state(string element)
{
	int i;
	for (i = 0; i < element.length(); i++)
		if (isdigit(element[i]))
			break;
	return atoi(element.substr(i).c_str());
}

string Parser::get_reduce_state(string element, int &pop_number)
{
	int l1 = -1, l2 = -1;
	int i;

	pop_number = 0;
	for (i = 0; i < element.length(); i++)
	{
		if (element[i] == ' ')
		{
			if (l1 == -1)
				l1 = i;
			else if (l2 == -1)
			{
				l2 = i;
			}
			pop_number++;
		}
	}
	
	pop_number -= 2;
	return element.substr(l1 + 1, l2 - l1 - 1);
}

int Parser::get_index(string *index, string target)
{
	for (int i = 0; i < ACTION_INDEX_LENGTH; i++)
		if (index[i] == target)
			return i;
	return -1;
}

void Parser::print_action_table()
{
	for (int i = 0; i < ACTION_TABLE_LENGTH; i++)
	{
		for (int j = 0; j < ACTION_TABLE_WIDTH; j++)
			cout << tab.action_table[i][j] << " ";
		cout << endl;
	}
}

void Parser::print_goto_table()
{
	for (int i = 0; i < GOTO_TABLE_LENGTH; i++)
	{
		for (int j = 0; j < GOTO_TABLE_WIDTH; j++)
			cout << tab.goto_table[i][j] << " ";
		cout << endl;
	}
}

void Parser::print_reduce_list()
{
	for (vector<string>::iterator it = reduce_list.begin();
			it != reduce_list.end(); it++)
		cout << *it << endl;
}

void Parser::syntax_directed(string reduce)
{
	Symbol symbol;
	Expression exp;
	string address;
	int production_index = production.get_index_of(reduce);
	vector<int> _array_value;
	vector<string> _some_variables;
	switch(production_index)
	{
		//type -> int
		case 1:
			{
				Symbol s(string("int"), string(" "), _some_variables, 0, baseAddr, _array_value, false);
				symbol_table.push_back(s);
				break;
			}
			//type -> float
		case 2:
			{
				Symbol s(string("int"), string(" "), _some_variables, 0, baseAddr, _array_value, false);
				symbol_table.push_back(s);
				break;
			}
		//variable -> identifiers
		case 9:
			symbol_table[symbol_table_index].is_array = false;
			break;
		//variable -> arrays
		case 10:
			symbol_table[symbol_table_index].is_array = true;
			break;
		//identifiers -> identifier
		case 11:
			symbol_table[symbol_table_index].some_variables.push_back(token_stack.top().value);
			break;
		//assign -> number
		case 13:
			exp.code.clear();
			exp.code.push_back(string("movl $") + token_stack.top().value + string(", %eax"));
			code_stack.push(exp);
			break;
		//assign -> identifier
		case 14:
			address = find_address(token_stack.top().value);
			exp.code.clear();
			exp.code.push_back(string("movl -") + address + string("(%ebp), %eax"));
			code_stack.push(exp);
			break;
		//expressions -> expression expression
		case 15:
			if (code_stack.size() >= 2)
			{
				Expression e1 = code_stack.top();
				code_stack.pop();
				Expression e2 = code_stack.top();
				code_stack.pop();
				e2.merge(e1.code);
				code_stack.push(e2);
			}
			break;
		//declarition -> type variable fen
		case 16:
			if (!symbol_table[symbol_table_index].is_array)
				symbol_table[symbol_table_index].size = symbol_table[symbol_table_index].some_variables.size();
			baseAddr += symbol_table[symbol_table_index].size * 4;
			symbol_table[symbol_table_index].address = baseAddr;
			symbol_table_index++;
			break;
		//arguments -> identifier
		case 17:
			exp.code.clear();
			exp.code.push_back(token_stack.top().value);
			code_stack.push(exp);
			break;
		//assigns -> identifier ++ fen
		case 20:
			{
				Token *tmp = get_stack_of(3);	//identifier
				address = find_address(tmp[0].value);
				exp.code.clear();
				exp.code.push_back(string("addl $1 , -") + address + string("(%ebp)"));
				code_stack.push(exp);
				break;
			}
		//identifiers -> identifiers , identifier
		case 21:
			symbol_table[symbol_table_index].some_variables.push_back(token_stack.top().value);
			break;
		//operation_high -> *
		case 23:
			exp.code.clear();
			exp.code.push_back(string("mull %ebx"));
			code_stack.push(exp);
			break;
		//operation_high -> /
		case 24:
			exp.code.clear();
			exp.code.push_back(string("movl %eax, %edx"));
			exp.code.push_back(string("movl %ebx, %eax"));
			exp.code.push_back(string("movl %edx, %ebx"));
			exp.code.push_back(string("movl $0 , %edx"));
			exp.code.push_back(string("divl %ebx"));
			code_stack.push(exp);
			break;
		//operation_pri -> +
		case 25:
			exp.code.clear();
			exp.code.push_back(string("addl %ecx, %eax"));
			code_stack.push(exp);
			break;
		//operation_pri -> -
		case 26:
			exp.code.clear();
			exp.code.push_back(string("subl %eax, %ecx"));
			exp.code.push_back(string("movl %ecx, %eax"));
			code_stack.push(exp);
			break;
		//assigns -> identifier = assign_pri fen
		case 27:
			{
				exp = code_stack.top();
				code_stack.pop();
				Token *tmp = get_stack_of(4);
				address = find_address(tmp[0].value);
				exp.code.push_back(string("movl %eax, -") + address + string("(%ebp)"));
				code_stack.push(exp);
				break;
			}
		//relate -> <=
		case 28:
			exp.code.clear();
			exp.generation(code_label, "jb");
			code_stack.push(exp);
			code_label++;
			break;
		//relate -> >=
		case 29:
			exp.code.clear();
			exp.generation(code_label, "ja");
			code_stack.push(exp);
			code_label++;
			break;
		//relate -> ==
		case 30:
			exp.code.clear();
			exp.generation(code_label, "jnz");
			code_stack.push(exp);
			code_label++;
			break;
		//relate -> <
		case 31:
			exp.code.clear();
			exp.generation(code_label, "jbe");
			code_stack.push(exp);
			code_label++;
			break;
		//relate -> >
		case 32:
			exp.code.clear();
			exp.generation(code_label, "jae");
			code_stack.push(exp);
			code_label++;
			break;
		//array_variable -> identifier [ identifier ]
		case 33:
			{
				Token* tmp = get_stack_of(4);
				string addr1 = find_address(tmp[0].value);
				string addr2 = find_address(tmp[2].value);
				exp.code.clear();
				exp.code.push_back(string("movl -") + addr2 + string("(%ebp), %edx"));
				exp.code.push_back(string("movl -") + addr1 + string("(%ebp,%edx,4) , %eax"));
				code_stack.push(exp);
				break;
			}
		//function -> identifier ( arguments ) fen
		case 34:
			{
				Token* tmp = get_stack_of(5);
				Expression e1 = code_stack.top();
				code_stack.pop();
				if (tmp[0].value == "printf")
				{
					if (e1.code.size() == 3)
					{
						string addr1 = find_address(e1.code[2]);
						string addr2 = find_address(e1.code[1]);
						string text = e1.code[0];
						text_msg.push_back(string("msg") + Parser::int_to_string(text_label) + string(":.asciz ") + text);
						exp.code.clear();
						exp.code.push_back(string("pushl -") + addr1 + string("(%ebp)"));
						exp.code.push_back(string("pushl -") + addr2 + string("(%ebp)"));
						exp.code.push_back(string("pushl $msg") + Parser::int_to_string(text_label));
						exp.code.push_back(string("call printf"));
						exp.code.push_back(string("addl $8, %esp"));
						text_label++;
						code_stack.push(exp);
					}
					else if (e1.code.size() == 2)
					{
						string addr = find_address(e1.code[1]);
						string text = e1.code[0];
						text_msg.push_back(string("msg") + int_to_string(text_label) + string(":.asciz ") + text);
						exp.code.push_back(string("pushl -") + addr + string("(%ebp)"));
						exp.code.push_back(string("pushl $msg") + Parser::int_to_string(text_label));
						exp.code.push_back(string("call printf"));
						exp.code.push_back(string("addl $8, %esp"));
						text_label++;
						code_stack.push(exp);
					}
					else if (e1.code.size() == 1)
					{
						string text = e1.code[0];
						text_msg.push_back(string("msg") + int_to_string(text_label) + string(":.asciz ") + text);
						exp.code.push_back(string("pushl $msg") + Parser::int_to_string(text_label));
						exp.code.push_back(string("call printf"));
						exp.code.push_back(string("addl $8, %esp"));
						text_label++;
						code_stack.push(exp);
					}
				}
				//scanf
				else
				{
					if (e1.code.size() <= 2)
					{
						string put = e1.code[1];
						string addr = find_address(put);
						string text = e1.code[0];

						text_msg.push_back(string("msg") + int_to_string(text_label) + string(":.asciz ") + text);
						exp.code.clear();
						exp.code.push_back(string("leal -") + addr + string("(%ebp) ,%eax"));
						exp.code.push_back(string("pushl %eax"));
						exp.code.push_back(string("pushl $msg") + int_to_string(text_label));
						exp.code.push_back(string("call scanf"));
						exp.code.push_back(string("addl $8, %esp"));
						text_label++;
						code_stack.push(exp);
					}
				}
				break;
			}
		//arguments -> arguments , identifier
		case 35:
			{
				exp.code.clear();
				exp.code.push_back(token_stack.top().value);
				Expression e1 = code_stack.top();
				code_stack.pop();
				e1.merge(exp.code);
				code_stack.push(e1);
				break;
			}
		//assign_high -> assign_high operation_high assign
		case 36:
			{
				Expression e1 = code_stack.top();
				code_stack.pop();
				Expression e2 = code_stack.top();
				code_stack.pop();
				Expression e3 = code_stack.top();
				code_stack.pop();
				e3.code.push_back(string("movl %eax, %ebx"));
				e3.merge(e1.code);
				e3.merge(e2.code);
				code_stack.push(e3);
				break;
			}
		//assign_pri -> assign_pri operation_pri assign_high
		case 37:
			{
				Expression e1 = code_stack.top();
				code_stack.pop();
				Expression e2 = code_stack.top();
				code_stack.pop();
				Expression e3 = code_stack.top();
				code_stack.pop();
				e3.code.push_back(string("movl %eax, %ecx"));
				e3.merge(e1.code);
				e3.merge(e2.code);
				code_stack.push(e3);
				break;
			}
		//relation -> identifier relate num
		case 38:
			{
				Token* tmp = get_stack_of(3);
				address = find_address(tmp[0].value);
				exp.code.clear();
				exp.code.push_back(string("movl -") + address + string("(%ebp) , %eax"));
				exp.code.push_back(string("movl $") + tmp[2].value + string(", %ebx"));
				exp.code.push_back(string("cmp %eax, %ebx"));
				code_stack.push(exp);
				break;
			}
		//relation -> identifier relate identifier
		case 39:
			{
				Token* tmp = get_stack_of(3);
				string addr1 = find_address(tmp[0].value);
				string addr2 = find_address(tmp[2].value);
				exp.code.clear();
				exp.code.push_back(string("movl -") + addr1 + string("(%ebp) , %eax"));
				exp.code.push_back(string("movl -") + addr2 + string("(%ebp) , %ebx"));
				exp.code.push_back(string("cmp %eax, %ebx"));
				code_stack.push(exp);
				break;
			}
		//subexpressions -> subexpressions subexpressions
		case 44:
			if (code_stack.size() >= 2)
			{
				Expression e1 = code_stack.top();
				code_stack.pop();
				Expression e2 = code_stack.top();
				code_stack.pop();
				e2.merge(e1.code);
				code_stack.push(e2);
			}
			break;
		//expression -> while ( relation ) { subexpressions }
		case 45:
			{
				Expression e1 = code_stack.top();
				code_stack.pop();
				Expression e2 = code_stack.top();
				code_stack.pop();
				Expression e3 = code_stack.top();
				code_stack.pop();

				e3.code.push_back(e3.while_start);
				e3.merge(e2.code);
				e3.code.push_back(e3.while_jmp_fail);
				e3.merge(e1.code);
				e3.code.push_back(e3.while_jmp_start);
				e3.code.push_back(e3.while_fail);
				code_stack.push(e3);
				break;
			}
		//nums -> num
		case 46:
			{
				int value = atoi(token_stack.top().value.c_str());
				symbol_table[symbol_table_index].size++;
				symbol_table[symbol_table_index].array_value.push_back(value);
				break;
			}
		//nums -> nums,num
		case 48:
			{
				int value = atoi(token_stack.top().value.c_str());
				symbol_table[symbol_table_index].size++;
				symbol_table[symbol_table_index].array_value.push_back(value);
				symbol_table[symbol_table_index].is_array = true;
				break;
			}
		//expression -> if ( relation ) { subexpressions } else { subexpressions }
		case 49:
			{
				Expression e1 = code_stack.top();
				code_stack.pop();
				Expression e2 = code_stack.top();
				code_stack.pop();
				Expression e3 = code_stack.top();
				code_stack.pop();
				Expression e4 = code_stack.top();
				code_stack.pop();

				e3.code.push_back(e4.if_start);
				e3.merge(e2.code);
				e3.code.push_back(e4.if_jmp_selection_end);
				e3.code.push_back(e4.if_fail);
				e3.merge(e1.code);
				e3.code.push_back(e4.if_selection_end);
				code_stack.push(e3);
				break;
			}
	}
}

string Parser::find_address(string value)
{
	int address = 0;

	for (vector<Symbol>::iterator it = symbol_table.begin();
			it != symbol_table.end(); it++)
		for (int i = 0; i < it->some_variables.size(); i++)
			if (it->some_variables[i] == value)
			{
				if (it->is_array)
					address = it->address;
				else
					address = it->address - 4 * it->some_variables.size() + 4 * ( i + 1);
			}
	
	return int_to_string(address);
}

string Parser::int_to_string(int num)
{
	char tmp[256];
	string res;

	sprintf(tmp, "%d", num);
	res = tmp;
	return res;
}

Token* Parser::get_stack_of(int num)
{
	Token *tmp = new Token[num];

	for (int i = 0; i < num; i++)
	{
		tmp[num - i - 1] = token_stack.top();
		token_stack.pop();
	}
	for (int i = 0; i < num; i++)
		token_stack.push(tmp[i]);
	return tmp;
}
