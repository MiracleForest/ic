#include "../../include/iLexer/iLexer.h"
using namespace MiracleForest::i::icFamily;
using uchar = unsigned char;
using uint  = unsigned int;

iLexer::iLexer(std::string inputCode)
    : _inputCode(inputCode)
    , _currentLine(0)
    , _pos(0)
    , _len(_inputCode.length())
{
}

iToken iLexer::read()
{
    int result = 0;
    // 找到有用token就返回
    while (_inputCode.length() > _pos)
    {
        if (_inputCode[_pos] == '\n')
        {
            _pos++;
            return iToken(iTokenID::EOL, _currentLine++, "");
        }

        if (result = readString(_pos))
        {
            auto rtstr  = _inputCode.substr(_pos, result);
            _pos       += result;
            rtstr       = rtstr.substr(1);
            rtstr       = rtstr.substr(0, rtstr.size() - 1);
            return iToken(iTokenID::String, _currentLine, rtstr);
        }

        if (result = readNumber(_pos))
        {
            auto rtstr  = _inputCode.substr(_pos, result);
            _pos       += result;
            string::replace(rtstr, "'", "");
            return iToken(iTokenID::Number, _currentLine, rtstr);
        }

        if (result = readIdentifier(_pos))
        {
            auto rtstr  = _inputCode.substr(_pos, result);
            _pos       += result;
            if (isKeyword(rtstr) == true) { return iToken(iTokenID::Keyword, _currentLine, rtstr); }
            return iToken(iTokenID::Identifier, _currentLine, rtstr);
        }

        if (result = readSpace(_pos)) { _pos += result; }
        else if (result = readLineComment(_pos))
        {
            _pos += result;
            _currentLine++;
        }
        else if (result = readBigComment(_pos)) { _pos += result; }
        else if (result = readOperator(_pos))
        {
            auto rtstr  = _inputCode.substr(_pos, result);
            _pos       += result;
            return iToken(iTokenID::Operator, _currentLine, rtstr);
        }
        else
        {
            std::string rtstr = _inputCode.substr(_pos, 1);
            _pos++;
            return iToken(iTokenID::Unk, _currentLine, rtstr);
        }
    }

    // 未找到可用Token，返回EOF
    return iToken(iTokenID::EOF_, _currentLine, "");
}


std::vector<iToken> iLexer::parse()
{
    std::vector<iToken> result {};
    iToken              tok {};
    while ((tok = read()).getID() != iTokenID::EOF_) { result.push_back(tok); }
    return result;
}

std::vector<iToken> iLexer::mergeConsecutiveStringsToken(CRef<std::vector<iToken>> input)
{
    std::vector<iToken> result;

    if (input.empty()) { return result; }

    iTokenID    currentID   = input[0].getID();
    std::string currentText = input[0].getText();
    int         currentLine = input[0].getLine();
    int         count       = 1;

    for (int i = 1; i < input.size(); i++)
    {
        if (input[i].getID() == currentID && input[i].getID() == iTokenID::String)
        {
            count++;
            currentText += input[i].getText();
        }
        else
        {
            if (count > 1) { result.push_back(iToken(currentID, currentLine, currentText)); }
            else { result.push_back(iToken(currentID, currentLine, currentText)); }

            currentID   = input[i].getID();
            currentText = input[i].getText();
            count       = 1;
        }
        currentLine = input[i].getLine();
    }

    if (count > 1) { result.push_back(iToken(currentID, currentLine, currentText)); }
    else { result.push_back(iToken(currentID, currentLine, currentText)); }

    return result;
}

int iLexer::readSpace(int pos)
{
    int result = 0;
    while (pos + result < _inputCode.length()
           && (_inputCode[pos + result] == ' ' || _inputCode[pos + result] == '\t'))
    {
        result++;
    }
    return result;
}

int iLexer::readString(int pos)
{

    int result = 0;
    if (_inputCode[pos] != '\"') { return 0; }
    // 左引号
    result++;

    while (pos + result < (_inputCode.length() - 1) && _inputCode[pos + result] != '\"')
    {
        // 只要没到底，没读完，那就继续读
        if (_inputCode[pos + result] == '\\')
        {
            // 转义字符不转，直接保留
            result++;
        }
        result++;
    }

    if (_inputCode[pos + result] != '\"')
    {
        // 没有右边的引号
        return 0;
    }
    // 右引号
    result++;
    return result;
}

int iLexer::readNumber(int pos)
{
    int result = 0;

    result = readHexNumber(pos);
    if (result) { return result; }

    result = readBinNumber(pos);
    if (result) { return result; }

    result = readOctNumber(pos);
    if (result) { return result; }

    result = readDecNumber(pos);
    if (result) { return result; }

    return 0;
}

int iLexer::readDecNumber(int pos)
{
    int result = 0;

    while (pos + result < _inputCode.length()
               && ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '9')
           || '\'' == _inputCode[pos + result])
    {
        result++;
    }
    if (_inputCode[pos + result] == '.') { result++; }
    while (pos + result < _inputCode.length()
               && ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '9')
           || '\'' == _inputCode[pos + result])
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
        // 长度过小
        return 0;
    }

    if (_inputCode[pos] == '0' && (_inputCode[pos + 1] == 'x' || _inputCode[pos + 1] == 'X')) { result += 2; }
    else { return 0; }

    while (pos + result < _inputCode.length()
           && (('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '9')
               || ('A' <= _inputCode[pos + result] && _inputCode[pos + result] <= 'F')
               || ('a' <= _inputCode[pos + result] && _inputCode[pos + result] <= 'f')))
    {
        result++;
    }
    return result;
}

int iLexer::readBinNumber(int pos)
{
    int result = 0;

    if (_inputCode.length() <= pos + 2)
    {
        // 长度过小
        return 0;
    }

    if (_inputCode[pos] == '0' && (_inputCode[pos + 1] == 'b' || _inputCode[pos + 1] == 'B')) { result += 2; }
    else { return 0; }

    while (pos + result < _inputCode.length()
           && (_inputCode[pos + result] == '0' || _inputCode[pos + result] == '1'))
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
        // 长度过小
        return 0;
    }

    if (_inputCode[pos] == '0') { result += 1; }
    else { return 0; }
    if (_inputCode.length() > pos + 1 && _inputCode[pos + 1] == '.') { return 0; }

    while (pos + result < _inputCode.length()
           && ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '8'))
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
        // 长度过小
        return 0;
    }

    if (_inputCode[pos] == '/' && _inputCode[pos + 1] == '/')
    {
        // 加上两个斜杠
        result += 2;
    }
    else { return 0; }

    while (pos + result < _inputCode.length() && _inputCode[pos + result] != '\n') { result++; }

    return result;
}

int iLexer::readBigComment(int pos)
{
    int result = 0;

    if (_inputCode.length() <= pos + 3) { return 0; }

    if (_inputCode[pos] == '/' && _inputCode[pos + 1] == '*')
    {
        // 加上/*
        result += 2;
    }
    else { return 0; }

    while (pos + result < (_inputCode.length() - 2)
           && (_inputCode[pos + result] != '*' || _inputCode[pos + result + 1] != '/'))
    {
        if (_inputCode[pos + result] == '\n') { _currentLine++; }
        result++;
    }

    // 加上*/
    result += 2;

    return result;
}

int iLexer::readIdentifier(int pos)
{
    int result = 0;
    if (('A' <= _inputCode[pos] && _inputCode[pos] <= 'Z')
        || ('a' <= _inputCode[pos] && _inputCode[pos] <= 'z') || _inputCode[pos] == '_')
    {
        result++;
    }
    while (pos + result < _inputCode.length()
           && (('A' <= _inputCode[pos + result] && _inputCode[pos + result] <= 'Z')
               || ('a' <= _inputCode[pos + result] && _inputCode[pos + result] <= 'z')
               || ('0' <= _inputCode[pos + result] && _inputCode[pos + result] <= '9')
               || _inputCode[pos + result] == '_'))
    {
        result++;
    }

    return result;
}

int iLexer::readOperator(int pos)
{
    std::string buff = "";

    for (int i = 0; vector::contains<std::string>(
             this->_operatorsSeparateCharacter,
             std::to_string(_inputCode[pos + i])
         );
         i++)
    {
        buff += std::to_string(_inputCode[pos + i]);
    }

    if (buff.size() > 3) { buff = buff.substr(0, 3); }

    if (buff.size() == 3 && vector::contains<std::string>(this->_operatorsMultipleCharacter, buff))
    {
        return 3;
    }
    buff = buff.substr(0, 2);
    if (buff.size() == 2 && vector::contains<std::string>(this->_operatorsMultipleCharacter, buff))
    {
        return 2;
    }
    buff = buff.substr(0, 1);
    if (buff.size() == 1 && vector::contains<std::string>(this->_operatorsSeparateCharacter, buff))
    {
        return 1;
    }

    return 0;
}

bool iLexer::isKeyword(std::string id) const
{
    for (auto& v : _keywords)
    {
        if (id == v) { return true; }
    }
    return false;
}

Ref<iLexer> iLexer::operator=(CRef<iLexer> l)
{
    this->_inputCode = l._inputCode;
    return *this;
}
