#include "../../include/iParse/iParser.h"
using namespace MiracleForest::i::icFamily;


iParser::iParser(CRef<std::vector<MiracleForest::i::icFamily::iToken>> tokens)
    : mTokens(tokens)
    , mCurrent(0)
    , mParseEnd(false)
{
}

iParser::~iParser() {}

Ptr<AST::iASTGlobalAreaNode> iParser::parse()
{
    if (this->mTokens.empty()) { return nullptr; }
    return this->program();
}