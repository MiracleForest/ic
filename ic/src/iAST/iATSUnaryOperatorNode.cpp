#include "../../include/iAST/iATSUnaryOperatorNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iATSUnaryOperatorNode::iATSUnaryOperatorNode()
	:data(nullptr)
	, iASTNode(nullptr, iASTNodeType::iATSUnaryOperatorNode, "iATSUnaryOperatorNode", 0, false, {})
{ }

iATSUnaryOperatorNode::iATSUnaryOperatorNode(_ISTD Ptr<iASTNode> data)
	:data(data)
	, iASTNode(nullptr, iASTNodeType::iATSUnaryOperatorNode, "iATSUnaryOperatorNode", 0, false, {})
{ }

iATSUnaryOperatorNode::~iATSUnaryOperatorNode()
{
	//_ISTD basic::iBasic<iASTNode>::destroy(parent);
}

_ISTD Ptr<iASTNode> iATSUnaryOperatorNode::get()const noexcept
{
	return data;
}

_ISTD Ptr<iATSUnaryOperatorNode> iATSUnaryOperatorNode::set(_ISTD Ptr<iASTNode> data)
{
	this->data = data;
	return this;
}