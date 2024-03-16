#include "../../include/iAST/iASTIntegerLiteralNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTIntegerLiteralNode::iASTIntegerLiteralNode()
    : data(0)
    , iASTNode(nullptr, iASTNodeType::iASTIntegerLiteralNode, "iASTIntegerLiteralNode", 0, false, {})
{
}

iASTIntegerLiteralNode::iASTIntegerLiteralNode(long long data)
    : data(data)
    , iASTNode(nullptr, iASTNodeType::iASTIntegerLiteralNode, "iASTIntegerLiteralNode", 0, false, {})
{
}

iASTIntegerLiteralNode::~iASTIntegerLiteralNode() {}


[[nodiscard]] long long iASTIntegerLiteralNode::get() const noexcept { return this->data; }

Ptr<iASTIntegerLiteralNode> iASTIntegerLiteralNode::set(long long data)
{
    this->data = data;
    return this;
}
