#include <iostream>
#include "lexical.h"
#include "parser.h"
#include "asm.h"

using namespace std;

int main()
{
	Lexical lexical;
	lexical.anylize();
//	lexical.print_token_list();
	
	Parser parser(lexical.token_list);
	parser.anylize();
//	parser.print_reduce_list();
	
	Asm as(parser.symbol_table, parser.code_stack.top(), parser.text_msg);
	as.make_asm();

	cout << "compile example/data.txt successfull!" << endl;
	cout << "Usage:\t[cd example]" << endl;
	cout << "\t[as data.s -o data.o]" << endl;
	cout << "\t[gcc data.o -o data]" << endl;

	return 0;
}
