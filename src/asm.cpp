#include <iostream>
#include "asm.h"
using namespace std;

Asm::Asm(vector<Symbol> symbol_table, Expression exp, vector<string> text_msg)
{
	this->symbol_table = symbol_table;
	this->exp = exp;
	this->text_msg.assign(text_msg.begin(), text_msg.end());
	output.open("example/data.s");
}

Asm::~Asm()
{
	output.close();
}

void Asm::make_asm()
{
	output << ".section .data" << endl;
	output << ".section .rodata" << endl;

	for (vector<string>::iterator it = text_msg.begin(); 
			it != text_msg.end(); it++)
		output << *it << endl;

	output << ".section .text" << endl;
	output << ".global main" << endl;
	output << "main:" << endl;
	output << "pushl %ebp" << endl;
	output << "movl %esp,%ebp" << endl;

	for (vector<Symbol>::iterator it = symbol_table.begin();
			it != symbol_table.end(); it++)
	{
		if (it->is_array)
		{
			output << "subl $" << it->size * 4 << ",%esp" << endl;
			for (int i = 0; i < it->array_value.size(); i++)
			{
				output << "movl $" << i << ", %edx" << endl;
				output << "movl $" << it->array_value[i] << ",-" << 
					it->address << "(%ebp, %edx, 4)" << endl;
			}
		}
		else
		{
			for (int i = 0; i < it->some_variables.size(); i++)
				output << "subl $4, %esp" << endl;
		}
	}
	
	for (vector<string>::iterator it = exp.code.begin();
			it != exp.code.end(); it++)
		output << *it << endl;

	output << "movl $1, %eax" << endl;
	output << "movl $0, %ebx" << endl;
	output << "int $0x80" << endl;
}
