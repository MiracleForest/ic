#include "../../include/iLexer/iToken.h"
using namespace i::icSystem;
using uchar = i::core::uchar;
using uint = i::core::uint;
using istring = _ISTDTEXT istring;

iToken::iToken(iTokenID token_id, istring text)
	:_ID(token_id), _text(text)
{ }

iToken::iToken()
	:_ID(iTokenID::Unk), _text("")
{ }

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

istring iToken::getText()const
{
	return this->_text;
}

iTokenID iToken::getID()const
{
	return this->_ID;
}

_ISTD Ref<iToken> iToken::operator=(_ISTD CRef<iToken> t)
{
	this->_ID = t.getID();
	this->_text = t.getText();
	return *this;
}
