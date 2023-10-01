#include "../../include/iAST/iATSBinaryOperatorNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iATSBinaryOperatorNode::iATSBinaryOperatorNode()
	:left(nullptr)
	, right(nullptr)
	, iASTNode(nullptr, iASTNodeType::iATSBinaryOperatorNode, "iATSBinaryOperatorNode", 0, false, {})
{ }

iATSBinaryOperatorNode::iATSBinaryOperatorNode(_ISTD Ptr<iASTNode> leftData, _ISTD Ptr<iASTNode> rightData)
	:left(leftData)
	, right(rightData)
	, iASTNode(nullptr, iASTNodeType::iATSBinaryOperatorNode, "iATSBinaryOperatorNode", 0, false, {})
{ }

iATSBinaryOperatorNode::~iATSBinaryOperatorNode()
{
	//_ISTD basic::iBasic<iASTNode>::destroy(parent);
}

_ISTD Ptr<iASTNode> iATSBinaryOperatorNode::getLeft()const noexcept
{
	return this->left;
}

_ISTD Ptr<iASTNode> iATSBinaryOperatorNode::getRight()const noexcept
{
	return this->right;
}

_ISTD Ptr<iATSBinaryOperatorNode> iATSBinaryOperatorNode::setLeft(_ISTD Ptr<iASTNode> leftData)
{
	this->left = leftData;
	return this;
}

_ISTD Ptr<iATSBinaryOperatorNode> iATSBinaryOperatorNode::setRight(_ISTD Ptr<iASTNode> rightData)
{
	this->left = rightData;
	return this;
}