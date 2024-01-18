#include "../../include/iAST/iATSUnaryOperatorNode.h"
using namespace MiracleForest::i::icFamily::AST;


iATSUnaryOperatorNode::iATSUnaryOperatorNode()
    : data(nullptr)
    , iASTNode(nullptr, iASTNodeType::iATSUnaryOperatorNode, "iATSUnaryOperatorNode", 0, false, {})
{
}

iATSUnaryOperatorNode::iATSUnaryOperatorNode(Ptr<iASTNode> data)
    : data(data)
    , iASTNode(nullptr, iASTNodeType::iATSUnaryOperatorNode, "iATSUnaryOperatorNode", 0, false, {})
{
}

iATSUnaryOperatorNode::~iATSUnaryOperatorNode()
{
    // basic::iBasic<iASTNode>::destroy(parent);
}

Ptr<iASTNode> iATSUnaryOperatorNode::get() const noexcept { return this->data; }

Ptr<iATSUnaryOperatorNode> iATSUnaryOperatorNode::set(Ptr<iASTNode> data)
{
    this->data = data;
    return this;
}