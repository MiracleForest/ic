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
	while (_inputCode != "")
	{
		int len = _inputCode.length();

		if (_inputCode[0] == '\n')
		{
			_inputCode = _inputCode.substr(1, _inputCode.length());
			return iToken(iTokenID::EOL, "");
		}

		if (result = readString())
		{
			auto rtstr = _inputCode.substr(0, result);
			_inputCode = _inputCode.substr(result, len);
			return iToken(iTokenID::String, rtstr);
		}

		if (result = readNumber())
		{
			auto rtstr = _inputCode.substr(0, result);
			_inputCode = _inputCode.substr(result, len);
			return iToken(iTokenID::Number, rtstr);
		}

		if (result = readIdentifier())
		{
			istring token_str = _inputCode.substr(0, result);
			_inputCode = _inputCode.substr(result, len);
			if (isKeyword(token_str) == true)
			{
				return iToken(iTokenID::Keyword, token_str);
			}
			return iToken(iTokenID::Identifier, token_str);
		}

		if (result = readSpace())
		{
			_inputCode = _inputCode.substr(result, len);
		}
		else if (result = readLineComment())
		{
			_inputCode = _inputCode.substr(result, len);
		}
		else if (result = readBigComment())
		{
			_inputCode = _inputCode.substr(result, len);
		}
		else
		{
			//到这里为止什么都没有，肯定是运算符
			istring op = _inputCode.substr(0, 1);
			_inputCode = _inputCode.substr(1, len);
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

int iLexer::readSpace()
{
	int result = 0;
	while (result < _inputCode.length() && (_inputCode[result] == ' ' || _inputCode[result] == '\t'))
	{
		result++;
	}
	return result;
}

int iLexer::readString()
{

	int result = 0;
	if (_inputCode[0] != '\"')
	{
		return 0;
	}
	//左引号
	result++;

	while (result < (_inputCode.length() - 1) && _inputCode[result] != '\"')
	{
		//只要没到底，没读完，那就继续读
		if (_inputCode[result] == '\\')
		{
			//转义字符不转，直接保留
			result++;
		}
		result++;
	}

	if (_inputCode[result] != '\"')
	{
		//没有右边的引号
		return 0;
	}
	//右引号
	result++;
	return result;
}

int iLexer::readNumber()
{
	int result = 0;

	result = readHexNumber();
	if (result != 0)
	{
		return result;
	}

	result = readOctNumber();
	if (result != 0)
	{
		return result;
	}

	result = readDecNumber();
	if (result != 0)
	{
		return result;
	}

	return 0;
}

int iLexer::readDecNumber()
{
	int result = 0;

	while (result < _inputCode.length() && ('0' <= _inputCode[result] && _inputCode[result] <= '9'))
	{
		result++;
	}

	return result;
}

int iLexer::readHexNumber()
{
	int result = 0;

	if (_inputCode.length() <= 2)
	{
		//长度过小
		return 0;
	}

	if (_inputCode[0] == '0' && _inputCode[1] == 'x')
	{
		result += 2;
	}
	else
	{
		return 0;
	}

	while (result < _inputCode.length() && ('0' <= _inputCode[result] && _inputCode[result] <= 'F'))
	{
		result++;
	}
	return result;
}

int iLexer::readOctNumber()
{
	int result = 0;

	if (_inputCode.length() <= 1)
	{
		//长度过小
		return 0;
	}

	if (_inputCode[0] == '0')
	{
		result += 1;
	}
	else
	{
		return 0;
	}
	//至少是个位数
	result++;

	while (result < _inputCode.length() && ('0' <= _inputCode[result] && _inputCode[result] <= '8'))
	{
		result++;
	}
	return result;
}

int iLexer::readLineComment()
{
	int result = 0;
	if (_inputCode.length() <= 1)
	{
		//长度过小
		return 0;
	}

	if (_inputCode[0] == '/' && _inputCode[1] == '/')
	{
		//加上两个斜杠
		result += 2;
	}
	else
	{
		return 0;
	}

	while (result < _inputCode.length() && _inputCode[result] != '\n')
	{
		result++;
	}

	return result;
}

int iLexer::readBigComment()
{
	int result = 0;

	if (_inputCode.length() <= 3)
	{
		return 0;
	}

	if (_inputCode[0] == '/' && _inputCode[1] == '*')
	{
		//加上/*
		result += 2;
	}
	else
	{
		return 0;
	}

	while (result < (_inputCode.length() - 2) && (_inputCode[result] != '*' || _inputCode[result + 1] != '/'))
	{
		result++;
	}

	//加上*/
	result += 2;

	return result;
}

int iLexer::readIdentifier()
{
	int result = 0;
	if (('A' <= _inputCode[0] && _inputCode[0] <= 'Z') || ('a' <= _inputCode[0] && _inputCode[0] <= 'z') || _inputCode[0] == '_')
	{
		result++;
	}
	while (result < _inputCode.length() && (('A' <= _inputCode[result] && _inputCode[result] <= 'Z') || ('a' <= _inputCode[result] && _inputCode[result] <= 'z') || ('0' <= _inputCode[result] && _inputCode[result] <= '9') || _inputCode[result] == '_'))
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
