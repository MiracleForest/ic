#include "../../include/iAST/iASTBinaryOperatorNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTBinaryOperatorNode::iASTBinaryOperatorNode()
    : left(nullptr)
    , right(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTBinaryOperatorNode, "iASTBinaryOperatorNode", 0, false, {})
{
}

iASTBinaryOperatorNode::iASTBinaryOperatorNode(Ptr<iASTNode> leftData, Ptr<iASTNode> rightData)
    : left(leftData)
    , right(rightData)
    , iASTNode(nullptr, iASTNodeType::iASTBinaryOperatorNode, "iASTBinaryOperatorNode", 0, false, {})
{
}

iASTBinaryOperatorNode::~iASTBinaryOperatorNode()
{
    // basic::iBasic<iASTNode>::destroy(parent);
}

Ptr<iASTNode> iASTBinaryOperatorNode::getLeft() const noexcept { return this->left; }

Ptr<iASTNode> iASTBinaryOperatorNode::getRight() const noexcept { return this->right; }

Ptr<iASTBinaryOperatorNode> iASTBinaryOperatorNode::setLeft(Ptr<iASTNode> leftData)
{
    this->left = leftData;
    return this;
}

Ptr<iASTBinaryOperatorNode> iASTBinaryOperatorNode::setRight(Ptr<iASTNode> rightData)
{
    this->left = rightData;
    return this;
}