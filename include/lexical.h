#ifndef LEXICAL_H
#define LEXICAL_H

#include <string>
#include <fstream>
#include <vector>
#include "token.h"
using namespace std;

class Lexical
{
public:
	Lexical();
	void anylize();
	void print_token_list();
	~Lexical();

	vector<Token> token_list;
private:
	int iskey(string key);
	int pattern_digit(string &line, int k);
	int pattern_alpha(string &line, int k);
	int pattern_quo(string &line, int k);

	ifstream input;
};

#endif
