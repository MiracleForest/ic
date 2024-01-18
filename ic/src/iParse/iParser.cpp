#include "../../include/iParse/iParser.h"
using namespace MiracleForest::i::icFamily;


iParser::iParser(CRef<std::vector<MiracleForest::i::icFamily::iToken>> tokens)
    : _tokens(tokens)
{
}

iParser::~iParser() {}

Ptr<AST::iASTGlobalAreaNode> iParser::parse()
{
    if (this->_tokens.empty()) { return nullptr; }
    return this->program();
}

Ptr<AST::iASTGlobalAreaNode> iParser::program()
{
    static Ptr<AST::iASTGlobalAreaNode> iAST;

    return iAST;
}
