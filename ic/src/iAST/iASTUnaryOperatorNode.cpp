#include "../../include/iAST/iASTUnaryOperatorNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTUnaryOperatorNode::iASTUnaryOperatorNode()
    : data(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTUnaryOperatorNode, "iASTUnaryOperatorNode", 0, false, {})
{
}

iASTUnaryOperatorNode::iASTUnaryOperatorNode(Ptr<iASTNode> data)
    : data(data)
    , iASTNode(nullptr, iASTNodeType::iASTUnaryOperatorNode, "iASTUnaryOperatorNode", 0, false, {})
{
}

iASTUnaryOperatorNode::~iASTUnaryOperatorNode()
{
    // basic::iBasic<iASTNode>::destroy(parent);
}

Ptr<iASTNode> iASTUnaryOperatorNode::get() const noexcept { return this->data; }

Ptr<iASTUnaryOperatorNode> iASTUnaryOperatorNode::set(Ptr<iASTNode> data)
{
    this->data = data;
    return this;
}