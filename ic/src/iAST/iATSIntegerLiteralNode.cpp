#include "../../include/iAST/iATSIntegerLiteralNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iATSIntegerLiteralNode::iATSIntegerLiteralNode()
	:data(0)
	, iASTNode(nullptr, iASTNodeType::iATSIntegerLiteralNode, "iATSIntegerLiteralNode", 0, false, {})
{ }

iATSIntegerLiteralNode::iATSIntegerLiteralNode(int64 data)
	:data(data)
	, iASTNode(nullptr, iASTNodeType::iATSIntegerLiteralNode, "iATSIntegerLiteralNode", 0, false, {})
{ }

iATSIntegerLiteralNode::~iATSIntegerLiteralNode()
{ }


[[nodiscard]] int64 iATSIntegerLiteralNode::get()const noexcept
{
	return this->data;
}

Ptr<iATSIntegerLiteralNode> iATSIntegerLiteralNode::set(int64 data)
{
	this->data = data;
	return this;
}
