#include "../../include/iAST/iASTStringLiteralNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTStringLiteralNode::iASTStringLiteralNode()
    : data("")
    , iASTNode(nullptr, iASTNodeType::iASTStringLiteralNode, "iASTStringLiteralNode", 0, false, {})
{
}

iASTStringLiteralNode::iASTStringLiteralNode(std::string data)
    : data(data)
    , iASTNode(nullptr, iASTNodeType::iASTStringLiteralNode, "iASTStringLiteralNode", 0, false, {})
{
}

iASTStringLiteralNode::~iASTStringLiteralNode()
{
    // basic::iBasic<iASTNode>::destroy(parent);
}


auto iASTStringLiteralNode::get() const noexcept -> std::string { return this->data; }

Ptr<iASTStringLiteralNode> iASTStringLiteralNode::set(CRef<std::string> data)
{
    this->data = data;
    return this;
}