#include "../../include/iAST/iATSTernaryOperatorNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iATSTernaryOperatorNode::iATSTernaryOperatorNode()
	:left(nullptr)
	, middle(nullptr)
	, right(nullptr)
	, iASTNode(nullptr, iASTNodeType::iATSTernaryOperatorNode, "iATSTernaryOperatorNode", 0, false, {})
{ }

iATSTernaryOperatorNode::iATSTernaryOperatorNode(_ISTD Ptr<iASTNode> leftData, _ISTD Ptr<iASTNode> middleData, _ISTD Ptr<iASTNode> rightData)
	:left(leftData)
	, middle(middleData)
	, right(rightData)
	, iASTNode(nullptr, iASTNodeType::iATSTernaryOperatorNode, "iATSTernaryOperatorNode", 0, false, {})
{ }

iATSTernaryOperatorNode::~iATSTernaryOperatorNode()
{
	//_ISTD basic::iBasic<iASTNode>::destroy(parent);
}

_ISTD Ptr<iASTNode> iATSTernaryOperatorNode::getLeft()const noexcept
{
	return left;
}

_ISTD Ptr<iASTNode> iATSTernaryOperatorNode::getMiddle()const noexcept
{
	return middle;
}

_ISTD Ptr<iASTNode> iATSTernaryOperatorNode::getRight()const noexcept
{
	return right;
}

_ISTD Ptr<iATSTernaryOperatorNode> iATSTernaryOperatorNode::setLeft(_ISTD Ptr<iASTNode> leftData)
{
	left = leftData;
	return this;
}

_ISTD Ptr<iATSTernaryOperatorNode> iATSTernaryOperatorNode::setMiddle(_ISTD Ptr<iASTNode> middleData)
{
	middle = middleData;
	return this;
}

_ISTD Ptr<iATSTernaryOperatorNode> iATSTernaryOperatorNode::setRight(_ISTD Ptr<iASTNode> rightData)
{
	left = rightData;
	return this;
}