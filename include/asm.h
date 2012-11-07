#ifndef ASM_H
#define ASM_H

#include <vector>
#include <fstream>
#include <string>
#include "token.h"
#include "symbol.h"
#include "expression.h"

class Asm
{
public:
	Asm(vector<Symbol> symbol_table, Expression exp, vector<string> text_msg);
	~Asm();
	void make_asm();
private:
	ofstream output;
	vector<Symbol> symbol_table;
	Expression exp;
	vector<string> text_msg;
};

#endif
