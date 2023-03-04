#include "../../include/iLexer/iToken.h"
using namespace i::icSystem;
using uchar = i::core::uchar;
using uint = i::core::uint;
using istring = _ISTDTEXT istring;


istring iToken::getID2String()const
{

	if (_ID == iTokenID::String)
	{
		return "string";
	}
	else if (_ID == iTokenID::Number)
	{
		return "number";
	}
	else if (_ID == iTokenID::Identifier)
	{
		return "identifier";
	}
	else if (_ID == iTokenID::Keyword)
	{
		return "keyword";
	}
	else if (_ID == iTokenID::Operator)
	{
		return "operator";
	}
	else if (_ID == iTokenID::EOL)
	{
		return "end-of-line";
	}
	else if (_ID == iTokenID::EOF)
	{
		return "end-of-file";
	}
	else
	{
		return "unkown";
	}
}

iToken::iToken(uchar token_id, istring text)
	:_ID(token_id),_text(text)
{ }

istring iToken::getText()
{
	return this->text;
}

uchar iToken::getID()
{
	return this->ID;
}
