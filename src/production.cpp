#include <vector>
#include <string>
#include "production.h"
using namespace std;

Production::Production()
{
	p_list.push_back("reduce declaritions -> declarition");
	//1 ----
	p_list.push_back("reduce type -> int");
	//2 ----
	p_list.push_back("reduce type -> float");
	//3 ---- do not need do
	p_list.push_back("reduce declaritions -> declaritions declarition");
	//4 
	p_list.push_back("reduce body -> declaritions expressions");
	//5 ---- do not need do
	p_list.push_back("reduce expressions -> expression");
	//6 ---- donot need do
	p_list.push_back("reduce expression -> function");
	//7 ---  donot need do
	p_list.push_back("reduce expression -> assigns");
	//8 duoyude
	p_list.push_back("reduce expression -> calculations");
	//9 ----
	p_list.push_back("reduce variable -> identifiers");
	//10 ----
	p_list.push_back("reduce variable -> arrays");
	//11 ---- 
	p_list.push_back("reduce identifiers -> identifier");
	//12 ----do not need do
	p_list.push_back("reduce assign -> array_variable");
	//13 ----
	p_list.push_back("reduce assign -> num");
	//14 ----
	p_list.push_back("reduce assign -> identifier");
	//15 ----
	p_list.push_back("reduce expressions -> expressions expression");
	//16 ---- 
	p_list.push_back("reduce declarition -> type variable fen");
	//17 ----
	p_list.push_back("reduce arguments -> identifier");
	//18 -don't need do
	p_list.push_back("reduce assign_high -> assign");
	//19 -don't need do
	p_list.push_back("reduce assign_pri -> assign_high");
	//20 ----
	p_list.push_back("reduce assigns -> identifier ++ fen");
	//21 ----
	p_list.push_back("reduce identifiers -> identifiers , identifier");
	//22
	p_list.push_back("reduce program -> int main ( ) { body return assign fen }");
	//23 ---- 
	p_list.push_back("reduce operation_high -> *");
	//24 ----
	p_list.push_back("reduce operation_high -> /");
	//25 ----
	p_list.push_back("reduce operation_pri -> +");
	//26 ----
	p_list.push_back("reduce operation_pri -> -");
	//27 ----
	p_list.push_back("reduce assigns -> identifier = assign_pri fen");
	//28  ----
	p_list.push_back("reduce relate -> <=");
	//29  ----
	p_list.push_back("reduce relate -> >=");
	//30  
	p_list.push_back("reduce relate -> ==");
	//31  ----
	p_list.push_back("reduce relate -> <");
	//32  ----
	p_list.push_back("reduce relate -> >");
	//33 ----
	p_list.push_back("reduce array_variable -> identifier [ identifier ]");
	//34 ----
	p_list.push_back("reduce function -> identifier ( arguments ) fen");
	//35 ----
	p_list.push_back("reduce arguments -> arguments , identifier");
	//36 ----
	p_list.push_back("reduce assign_high -> assign_high operation_high assign");
	//37 ----
	p_list.push_back("reduce assign_pri -> assign_pri operation_pri assign_high");
	//38 ----
	p_list.push_back("reduce relation -> identifier relate num");
	//39 ----
	p_list.push_back("reduce relation -> identifier relate identifier");
	//40
	p_list.push_back("reduce subexpression -> function");
	//41
	p_list.push_back("reduce subexpression -> assigns");
	//42
	p_list.push_back("reduce subexpressions -> subexpression");
	//43  --- duoyude
	p_list.push_back("reduce subexpression -> calculations");
	//44  ----
	p_list.push_back("reduce subexpressions -> subexpressions subexpression");
	//45  ----
	p_list.push_back("reduce expression -> while ( relation ) { subexpressions }");
	//46 ----
	p_list.push_back("reduce nums -> num");
	//47 ---- do not need do
	p_list.push_back("reduce arrays -> identifiers [ num ] = { nums }");
	//48 ----
	p_list.push_back("reduce nums -> nums , num");
	//49 ----
	p_list.push_back("reduce expression -> if ( relation ) { subexpressions } else { subexpressions }");
}

int Production::get_index_of(string element)
{
	int i = 0;
	for (vector<string>::iterator it = p_list.begin();
			it != p_list.end(); it++, i++)
		if ((*it) == element)
			return i;
	return -1;
}
