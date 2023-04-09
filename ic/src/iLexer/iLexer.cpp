#include "../../include/iLexer/iLexer.h"
using namespace i::icSystem;
using uchar = _ISTD uchar;
using uint = _ISTD uint;
using istring = _ISTDTEXT istring;
using iLogger = _ISTD io::iLogger;


iLexer::iLexer(istring targetCode)
	:_inputCode(targetCode)
{ }

iToken iLexer::read()
{
	int result = 0;
	//找到有用token就返回
	while (_inputCode.length() > pos)
	{
		if (_inputCode[pos] == '\n')
		{
			pos++;
			return iToken(iTokenID::EOL, "");
		}

		if (result = readString(pos))
		{
			auto rtstr = _inputCode.substr(pos, result);
			pos += result;
			return iToken(iTokenID::String, rtstr);
		}

		if (result = readNumber(pos))
		{
			auto rtstr = _inputCode.substr(pos, result);
			pos += result;
			return iToken(iTokenID::Number, rtstr);
		}

		if (result = readIdentifier(pos))
		{
			istring token_str = _inputCode.substr(pos, result);
			pos += result;
			if (isKeyword(token_str) == true)
			{
				return iToken(iTokenID::Keyword, token_str);
			}
			return iToken(iTokenID::Identifier, token_str);
		}

		if (result = readSpace(pos))
		{
			pos += result;
		}
		else if (result = readLineComment(pos))
		{
			pos += result;
		}
		else if (result = readBigComment(pos))
		{
			pos += result;
		}
		else
		{
			//到这里为止什么都没有，肯定是运算符
			istring op = _inputCode.substr(pos, 1);
			pos++;
			return iToken(iTokenID::Operator, op);
		}
	}

	//未找到可用Token，返回EOF
	return iToken(iTokenID::EOF, "");
}


std::vector<iToken> iLexer::parse()
{
	std::vector<iToken> result;
	iToken tok;
	while ((tok = read()).getID() != iTokenID::EOF)
	{
		result.push_back(tok);
	}
	return result;
}

int iLexer::readSpace(int pos)
{
	int result = 0;
	while (pos + result < _inputCode.length() && (_inputCode[pos + result] == ' ' || _inputCode[pos + result] == '\t'))
	{
		result++;
	}
	return result;
}

int iLexer::readString(int pos)
{

	int result = 0;
	if (_inputCode[pos] != '\"')
	{
		return 0;
	}
	//左引号
	result++;

	while (pos + result < (_inputCode.length() - 1) && _inputCode[pos + result] != '\"')
	{
		//只要没到底，没读完，那就继续读
		if (_inputCode[pos + result] == '\\')
		{
			//转义字符不转，直接保留
			result++;
		}
		result++;
	}

	if (_inputCode[pos + result] != '\"')
	{
		//没有右边的引号
		return 0;
	}
	//右引号
	result++;
	return result;
}

int iLexer::readNumber(int pos)
{
	int result = 0;

	result = readHexNumber(pos);
	if (result != 0)
	{
		return result;
	}

	result = readOctNumber(pos);
	if (result != 0)
	{
		return result;
	}

	result = readDecNumber(pos);
	if (result != 0)
	{
		return result;
	}

	return 0;
}

int iLexer::readDecNumber(int pos)
{
	int result = 0;

	while (pos + result < _inputCode.length() && ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '9'))
	{
		result++;
	}

	return result;
}

int iLexer::readHexNumber(int pos)
{
	int result = 0;

	if (_inputCode.length() <= pos + 2)
	{
		//长度过小
		return 0;
	}

	if (_inputCode[pos] == '0' && _inputCode[pos + 1] == 'x')
	{
		result += 2;
	}
	else
	{
		return 0;
	}

	while (pos + result < _inputCode.length() && ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= 'F'))
	{
		result++;
	}
	return result;
}

int iLexer::readOctNumber(int pos)
{
	int result = 0;

	if (_inputCode.length() <= pos + 1)
	{
		//长度过小
		return 0;
	}

	if (_inputCode[pos] == '0')
	{
		result += 1;
	}
	else
	{
		return 0;
	}
	//至少是个位数
	result++;

	while (pos + result < _inputCode.length() && ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '8'))
	{
		result++;
	}
	return result;
}

int iLexer::readLineComment(int pos)
{
	int result = 0;
	if (_inputCode.length() <= pos + 1)
	{
		//长度过小
		return 0;
	}

	if (_inputCode[pos] == '/' && _inputCode[pos + 1] == '/')
	{
		//加上两个斜杠
		result += 2;
	}
	else
	{
		return 0;
	}

	while (pos + result < _inputCode.length() && _inputCode[pos + result] != '\n')
	{
		result++;
	}

	return result;
}

int iLexer::readBigComment(int pos)
{
	int result = 0;

	if (_inputCode.length() <= pos + 3)
	{
		return 0;
	}

	if (_inputCode[pos] == '/' && _inputCode[pos + 1] == '*')
	{
		//加上/*
		result += 2;
	}
	else
	{
		return 0;
	}

	while (pos + result < (_inputCode.length() - 2) && (_inputCode[pos + result] != '*' || _inputCode[pos + result + 1] != '/'))
	{
		result++;
	}

	//加上*/
	result += 2;

	return result;
}

int iLexer::readIdentifier(int pos)
{
	int result = 0;
	if (('A' <= _inputCode[pos] && _inputCode[pos] <= 'Z') || ('a' <= _inputCode[pos] && _inputCode[pos] <= 'z') || _inputCode[pos] == '_')
	{
		result++;
	}
	while (pos + result < _inputCode.length() && (('A' <= _inputCode[pos + result] && _inputCode[pos + result] <= 'Z') || ('a' <= _inputCode[pos + result] && _inputCode[pos + result] <= 'z') || ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '9') || _inputCode[pos + result] == '_'))
	{
		result++;
	}

	return result;
}

bool iLexer::isKeyword(istring id)const
{
	for (auto& v : _keywords)
	{
		if (id == v)
		{
			return true;
		}
	}
	return false;
}

_ISTD Ref<iLexer> iLexer::operator=(_ISTD CRef<iLexer> l)
{
	this->_inputCode = l._inputCode;
	return *this;
}
