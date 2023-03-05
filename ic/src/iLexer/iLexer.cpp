#include "../../include/iLexer/iLexer.h"
using namespace i::icSystem;
using uchar = _ISTD uchar;
using uint = _ISTD uint;
using istring = _ISTDTEXT istring;

iLexer::iLexer(istring targetCode)
	:_targetCode(targetCode)
{ }

iToken iLexer::read()
{
	int result = 0;
	//找到有用token就返回
	while (_targetCode != "")
	{
		int len = _targetCode.length();

		if (_targetCode[0] == '\n')
		{
			_targetCode = _targetCode.substr(1, _targetCode.length());
			return iToken(iTokenID::EOL, "");
		}

		if (result = readString())
		{
			//text = text[result:]
			_targetCode = _targetCode.substr(result, len);
			return iToken(iTokenID::String, _targetCode.substr(0, result));
		}

		if (result = readNumber())
		{
			_targetCode = _targetCode.substr(result, len);
			return iToken(iTokenID::Number, _targetCode.substr(0, result));
		}

		if (result = readIdentifier())
		{
			istring token_str = _targetCode.substr(0, result);
			_targetCode = _targetCode.substr(result, len);
			if (isKeyword(token_str) == true)
			{
				return iToken(iTokenID::Keyword, token_str);
			}
			return iToken(iTokenID::Identifier, token_str);
		}

		if (result = readSpace())
		{
			_targetCode = _targetCode.substr(result, len);
		}
		else if (result = readLineComment())
		{
			_targetCode = _targetCode.substr(result, len);
		}
		else if (result = readBigComment())
		{
			_targetCode = _targetCode.substr(result, len);
		}
		else
		{
			//到这里为止什么都没有，肯定是运算符
			istring op = _targetCode.substr(0, 1);
			_targetCode = _targetCode.substr(1, len);
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
	while (result < _targetCode.length() && (_targetCode[result] == ' ' || _targetCode[result] == '\t'))
	{
		result++;
	}
	return result;
}

int iLexer::readString()
{
	int result = 0;
	if (_targetCode[0] != '\"')
	{
		return 0;
	}
	//左引号
	result++;

	while (result < (_targetCode.length() - 1) && _targetCode[result] != '\"')
	{
		//只要没到底，没读完，那就继续读
		if (_targetCode[result] == '\\')
		{
			//转义字符不转，直接保留
			result++;
		}
		result++;
	}

	if (_targetCode[result] != '\"')
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

	while (result < _targetCode.length() && ('0' <= _targetCode[result] && _targetCode[result] <= '9'))
	{
		result++;
	}

	return result;
}

int iLexer::readHexNumber()
{
	int result = 0;

	if (_targetCode.length() <= 2)
	{
		//长度过小
		return 0;
	}

	if (_targetCode[0] == '0' && _targetCode[1] == 'x')
	{
		result += 2;
	}
	else
	{
		return 0;
	}

	while (result < _targetCode.length() && ('0' <= _targetCode[result] && _targetCode[result] <= 'F'))
	{
		result++;
	}
	return result;
}

int iLexer::readOctNumber()
{
	int result = 0;

	if (_targetCode.length() <= 1)
	{
		//长度过小
		return 0;
	}

	if (_targetCode[0] == '0')
	{
		result += 1;
	}
	else
	{
		return 0;
	}
	//至少是个位数
	result++;

	while (result < _targetCode.length() && ('0' <= _targetCode[result] && _targetCode[result] <= '8'))
	{
		result++;
	}
	return result;
}

int iLexer::readLineComment()
{
	int result = 0;
	if (_targetCode.length() <= 1)
	{
		//长度过小
		return 0;
	}

	if (_targetCode[0] == '/' && _targetCode[1] == '/')
	{
		//加上两个斜杠
		result += 2;
	}
	else
	{
		return 0;
	}

	while (result < _targetCode.length() && _targetCode[result] != '\n')
	{
		result++;
	}

	return result;
}

int iLexer::readBigComment()
{
	int result = 0;

	if (_targetCode.length() <= 3)
	{
		return 0;
	}

	if (_targetCode[0] == '/' && _targetCode[1] == '*')
	{
		//加上/*
		result += 2;
	}
	else
	{
		return 0;
	}

	while (result < (_targetCode.length() - 2) && (_targetCode[result] != '*' || _targetCode[result + 1] != '/'))
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
	if (('A' <= _targetCode[0] && _targetCode[0] <= 'Z') || ('a' <= _targetCode[0] && _targetCode[0] <= 'z') || _targetCode[0] == '_')
	{
		result++;
	}
	while (result < _targetCode.length() && (('A' <= _targetCode[result] && _targetCode[result] <= 'Z') || ('a' <= _targetCode[result] && _targetCode[result] <= 'z') || ('0' <= _targetCode[result] && _targetCode[result] <= '9') || _targetCode[result] == '_'))
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
	this->_targetCode = l._targetCode;
	return *this;
}
