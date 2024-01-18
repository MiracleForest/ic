#include "../../include/iAST/iATSIntegerLiteralNode.h"
using namespace MiracleForest::i::icFamily::AST;


iATSIntegerLiteralNode::iATSIntegerLiteralNode()
    : data(0)
    , iASTNode(nullptr, iASTNodeType::iATSIntegerLiteralNode, "iATSIntegerLiteralNode", 0, false, {})
{
}

iATSIntegerLiteralNode::iATSIntegerLiteralNode(long long data)
    : data(data)
    , iASTNode(nullptr, iASTNodeType::iATSIntegerLiteralNode, "iATSIntegerLiteralNode", 0, false, {})
{
}

iATSIntegerLiteralNode::~iATSIntegerLiteralNode() {}


[[nodiscard]] long long iATSIntegerLiteralNode::get() const noexcept { return this->data; }

Ptr<iATSIntegerLiteralNode> iATSIntegerLiteralNode::set(long long data)
{
    this->data = data;
    return this;
}
