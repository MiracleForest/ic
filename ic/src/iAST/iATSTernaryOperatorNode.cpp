#include "../../include/iAST/iATSTernaryOperatorNode.h"
using namespace MiracleForest::i::icFamily::AST;


iATSTernaryOperatorNode::iATSTernaryOperatorNode()
    : left(nullptr)
    , middle(nullptr)
    , right(nullptr)
    , iASTNode(nullptr, iASTNodeType::iATSTernaryOperatorNode, "iATSTernaryOperatorNode", 0, false, {})
{
}

iATSTernaryOperatorNode::iATSTernaryOperatorNode(
    Ptr<iASTNode> leftData,
    Ptr<iASTNode> middleData,
    Ptr<iASTNode> rightData
)
    : left(leftData)
    , middle(middleData)
    , right(rightData)
    , iASTNode(nullptr, iASTNodeType::iATSTernaryOperatorNode, "iATSTernaryOperatorNode", 0, false, {})
{
}

iATSTernaryOperatorNode::~iATSTernaryOperatorNode()
{
    // basic::iBasic<iASTNode>::destroy(parent);
}

Ptr<iASTNode> iATSTernaryOperatorNode::getLeft() const noexcept { return this->left; }

Ptr<iASTNode> iATSTernaryOperatorNode::getMiddle() const noexcept { return this->middle; }

Ptr<iASTNode> iATSTernaryOperatorNode::getRight() const noexcept { return this->right; }

Ptr<iATSTernaryOperatorNode> iATSTernaryOperatorNode::setLeft(Ptr<iASTNode> leftData)
{
    this->left = leftData;
    return this;
}

Ptr<iATSTernaryOperatorNode> iATSTernaryOperatorNode::setMiddle(Ptr<iASTNode> middleData)
{
    this->middle = middleData;
    return this;
}

Ptr<iATSTernaryOperatorNode> iATSTernaryOperatorNode::setRight(Ptr<iASTNode> rightData)
{
    this->left = rightData;
    return this;
}