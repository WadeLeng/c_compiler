#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

class Token
{
public:
	Token();
	Token(string type, string value);

	string type;
	string value;
};

#endif
