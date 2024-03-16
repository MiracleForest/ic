#include "../../include/iAST/iASTTernaryOperatorNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTTernaryOperatorNode::iASTTernaryOperatorNode()
    : left(nullptr)
    , middle(nullptr)
    , right(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTTernaryOperatorNode, "iASTTernaryOperatorNode", 0, false, {})
{
}

iASTTernaryOperatorNode::iASTTernaryOperatorNode(
    Ptr<iASTNode> leftData,
    Ptr<iASTNode> middleData,
    Ptr<iASTNode> rightData
)
    : left(leftData)
    , middle(middleData)
    , right(rightData)
    , iASTNode(nullptr, iASTNodeType::iASTTernaryOperatorNode, "iASTTernaryOperatorNode", 0, false, {})
{
}

iASTTernaryOperatorNode::~iASTTernaryOperatorNode()
{
    // basic::iBasic<iASTNode>::destroy(parent);
}

Ptr<iASTNode> iASTTernaryOperatorNode::getLeft() const noexcept { return this->left; }

Ptr<iASTNode> iASTTernaryOperatorNode::getMiddle() const noexcept { return this->middle; }

Ptr<iASTNode> iASTTernaryOperatorNode::getRight() const noexcept { return this->right; }

Ptr<iASTTernaryOperatorNode> iASTTernaryOperatorNode::setLeft(Ptr<iASTNode> leftData)
{
    this->left = leftData;
    return this;
}

Ptr<iASTTernaryOperatorNode> iASTTernaryOperatorNode::setMiddle(Ptr<iASTNode> middleData)
{
    this->middle = middleData;
    return this;
}

Ptr<iASTTernaryOperatorNode> iASTTernaryOperatorNode::setRight(Ptr<iASTNode> rightData)
{
    this->left = rightData;
    return this;
}