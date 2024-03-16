#include "../../include/iAST/iASTFloatingLiteralNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTFloatingLiteralNode::iASTFloatingLiteralNode()
    : data(.0)
    , iASTNode(nullptr, iASTNodeType::iASTFloatingLiteralNode, "iASTFloatingLiteralNode", 0, false, {})
{
}

iASTFloatingLiteralNode::iASTFloatingLiteralNode(double data)
    : data(data)
    , iASTNode(nullptr, iASTNodeType::iASTFloatingLiteralNode, "iASTFloatingLiteralNode", 0, false, {})
{
}

iASTFloatingLiteralNode::~iASTFloatingLiteralNode() {}


auto iASTFloatingLiteralNode::get() const noexcept -> double { return this->data; }

Ptr<iASTFloatingLiteralNode> iASTFloatingLiteralNode::set(double data)
{
    this->data = data;
    return this;
}
