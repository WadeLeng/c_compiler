#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include "lexical.h"
using namespace std;

Lexical::Lexical()
{
	input.open("example/data.txt");
	token_list.clear();
}

void Lexical::anylize()
{
	string line;
	while (!input.eof())
	{
		getline(input, line);
		if (line.empty()) continue;
		for (int i = 0; i < line.length(); i++)
		{
			if (isdigit(line[i]))
			{
				i = pattern_digit(line, i);
			}
			else if (isalpha(line[i]) || line[i] == '_')
			{
				i = pattern_alpha(line, i);
			}else if (line[i] == '"')
			{
				i = pattern_quo(line, i);
			}else if (line[i] == '+' || line[i] == '-' || line[i] == '=')
			{
				if (line[i] == line[i + 1])
				{
					Token tmp(line.substr(i, 2), line.substr(i, 2));
					token_list.push_back(tmp);
					i++;
				}else
				{
					Token tmp(line.substr(i, 1), line.substr(i, 1));
					token_list.push_back(tmp);
				}
			}else if (line[i] == '/' || line[i] == '*' || line[i] == '[' || line[i] == ']' ||
					line[i] == '{' || line[i] == '}' || line[i] == '#' || line[i] == ',' ||
					line[i] == '(' || line[i] == ')')
			{
				Token tmp(line.substr(i, 1), line.substr(i, 1));
				token_list.push_back(tmp);
			}else if (line[i] == '<' || line[i] == '>')
			{
				if (line[i + 1] == '=')
				{
					Token tmp(line.substr(i, 2), line.substr(i, 2));
					token_list.push_back(tmp);
					i++;
				}else
				{
					Token tmp(line.substr(i, 1), line.substr(i, 1));
					token_list.push_back(tmp);
				}
			}else if (line[i] == '\n' || line[i] == ' ')
			{
			}else if (line[i] == ';')
			{
				Token tmp("fen", line.substr(i, 1));
				token_list.push_back(tmp);
			}
		}
	}
	Token tmp("$", "$");
	token_list.push_back(tmp);

}
void Lexical::print_token_list()
{
	vector <Token> :: iterator it;
	for (it = token_list.begin(); it != token_list.end(); it++)
		cout << it->type << " " << it->value << endl;
}

Lexical::~Lexical()
{
	input.close();
}

int Lexical::iskey(string key)
{
	if (key == "if" || key == "else" || key == "while" || key == "for" || key == "int" || 
			key == "return" || key == "main" || key == "float")
		return true;
	else return false;
}

int Lexical::pattern_digit(string &line, int k)
{
	int i;
	for (i = k; i < line.length(); i++)
		if (!isdigit(line[i]))
			break;
	Token tmp("num", line.substr(k, i - k));
	token_list.push_back(tmp);
	return i - 1;
}

int Lexical::pattern_alpha(string &line, int k)
{
	int i;
	Token tmp;
	for (i = k; i < line.length(); i++)
		if (!isalpha(line[i]) && line[i] != '_' && !isdigit(line[i]))
			break;
	tmp.value = line.substr(k, i - k);
	if (iskey(tmp.value))
		tmp.type = tmp.value;
	else
		tmp.type = "identifier";
	token_list.push_back(tmp);
	return i - 1;
}

int Lexical::pattern_quo(string &line, int k)
{
	int i;
	for (i = k + 1; i < line.length(); i++)
		if (line[i] == '"')
			break;
	Token tmp("identifier", line.substr(k, i - k + 1));
	token_list.push_back(tmp);
	return i;
}
