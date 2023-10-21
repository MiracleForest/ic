#include "../../include/iAST/iATSBinaryOperatorNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iATSBinaryOperatorNode::iATSBinaryOperatorNode()
	:left(nullptr)
	, right(nullptr)
	, iASTNode(nullptr, iASTNodeType::iATSBinaryOperatorNode, "iATSBinaryOperatorNode", 0, false, {})
{ }

iATSBinaryOperatorNode::iATSBinaryOperatorNode(Ptr<iASTNode> leftData, Ptr<iASTNode> rightData)
	:left(leftData)
	, right(rightData)
	, iASTNode(nullptr, iASTNodeType::iATSBinaryOperatorNode, "iATSBinaryOperatorNode", 0, false, {})
{ }

iATSBinaryOperatorNode::~iATSBinaryOperatorNode()
{
	//basic::iBasic<iASTNode>::destroy(parent);
}

Ptr<iASTNode> iATSBinaryOperatorNode::getLeft()const noexcept
{
	return this->left;
}

Ptr<iASTNode> iATSBinaryOperatorNode::getRight()const noexcept
{
	return this->right;
}

Ptr<iATSBinaryOperatorNode> iATSBinaryOperatorNode::setLeft(Ptr<iASTNode> leftData)
{
	this->left = leftData;
	return this;
}

Ptr<iATSBinaryOperatorNode> iATSBinaryOperatorNode::setRight(Ptr<iASTNode> rightData)
{
	this->left = rightData;
	return this;
}