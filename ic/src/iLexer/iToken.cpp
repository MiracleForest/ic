#include "../../include/iLexer/iToken.h"
using namespace i::icFamily;
using namespace i::core;
using istring = _ISTDTEXT istring;

iToken::iToken(iTokenID token_id, int currentLine, istring text)
	: _ID(token_id)
	, _text(text)
	, _currentLine(currentLine)
{ }

iToken::iToken()
	: _ID(iTokenID::Unk)
	, _text("")
	, _currentLine(0)
{ }

iToken::iToken(CRef<iToken> itoken)
	: _ID(itoken._ID)
	, _text(itoken._text)
	, _currentLine(itoken._currentLine)
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

istring iToken::getText()const noexcept
{
	return this->_text;
}

void iToken::setText(_ISTD CRef<istring> text)
{
	this->_text = text;
}

iTokenID iToken::getID()const noexcept
{
	return this->_ID;
}

_ISTD Ref<iToken> iToken::operator=(_ISTD CRef<iToken> t)
{
	this->_ID = t.getID();
	this->_text = t.getText();
	this->_currentLine = t.getLine();
	return *this;
}

int iToken::getLine()const noexcept
{
	return _currentLine;
}