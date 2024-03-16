#include "../../include/iAST/iASTReturnStatementNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTReturnStatementNode::iASTReturnStatementNode()
    : value(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTReturnStatementNode, "iASTReturnStatementNode", 0, false, {})
{
}

iASTReturnStatementNode::iASTReturnStatementNode(Ptr<iASTNode> value)
    : value(value)
    , iASTNode(nullptr, iASTNodeType::iASTReturnStatementNode, "iASTReturnStatementNode", 0, false, {})
{
}

iASTReturnStatementNode::~iASTReturnStatementNode() {}

Ptr<iASTNode> iASTReturnStatementNode::getReturnValue() const noexcept { return value; }

Ptr<iASTReturnStatementNode> iASTReturnStatementNode::setReturnValue(Ptr<iASTNode> pvalue)
{
    this->value = value;
    return this;
}
