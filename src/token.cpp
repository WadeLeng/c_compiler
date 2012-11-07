#include <string>
#include "token.h"

Token::Token()
{
	type = "";
	value = "";
}

Token::Token(string type, string value)
{
	this->type = type;
	this->value = value;
}


