#include "../../include/iAST/iATSReturnStatementNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iATSReturnStatementNode::iATSReturnStatementNode()
	: value(nullptr)
	, iASTNode(nullptr, iASTNodeType::iATSReturnStatementNode, "iATSReturnStatementNode", 0, false, {})
{ }

iATSReturnStatementNode::iATSReturnStatementNode(Ptr<iASTNode> value)
	: value(value)
	, iASTNode(nullptr, iASTNodeType::iATSReturnStatementNode, "iATSReturnStatementNode", 0, false, {})
{ }

iATSReturnStatementNode::~iATSReturnStatementNode()
{ }

Ptr<iASTNode> iATSReturnStatementNode::getReturnValue()const noexcept
{
	return value;
}

Ptr<iATSReturnStatementNode> iATSReturnStatementNode::setReturnValue(Ptr<iASTNode> pvalue)
{
	this->value = value;
	return this;
}
