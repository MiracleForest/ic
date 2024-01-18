#include "../../include/iLexer/iToken.h"
using namespace MiracleForest::i::icFamily;



iToken::iToken(iTokenID token_id, int currentLine, std::string text)
    : _ID(token_id)
    , _text(text)
    , _currentLine(currentLine)
{
}

iToken::iToken()
    : _ID(iTokenID::Unk)
    , _text("")
    , _currentLine(0)
{
}

iToken::iToken(CRef<iToken> itoken)
    : _ID(itoken._ID)
    , _text(itoken._text)
    , _currentLine(itoken._currentLine)
{
}

std::string iToken::getID2String() const
{

    if (_ID == iTokenID::String) { return "string"; }
    else if (_ID == iTokenID::Number) { return "number"; }
    else if (_ID == iTokenID::Identifier) { return "identifier"; }
    else if (_ID == iTokenID::Keyword) { return "keyword"; }
    else if (_ID == iTokenID::Operator) { return "operator"; }
    else if (_ID == iTokenID::EOL) { return "end-of-line"; }
    else if (_ID == iTokenID::EOF_) { return "end-of-file"; }
    else { return "unkown"; }
}

std::string iToken::getText() const noexcept { return this->_text; }

void iToken::setText(CRef<std::string> text) { this->_text = text; }

iTokenID iToken::getID() const noexcept { return this->_ID; }

Ref<iToken> iToken::operator=(CRef<iToken> t)
{
    this->_ID          = t.getID();
    this->_text        = t.getText();
    this->_currentLine = t.getLine();
    return *this;
}

int iToken::getLine() const noexcept { return _currentLine; }