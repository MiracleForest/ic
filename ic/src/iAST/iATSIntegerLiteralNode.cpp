#include "../../include/iAST/iATSIntegerLiteralNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iATSIntegerLiteralNode::iATSIntegerLiteralNode()
	:data(0)
{ }

iATSIntegerLiteralNode::iATSIntegerLiteralNode(_ISTD int64 data)
	:data(data)
{ }

iATSIntegerLiteralNode::~iATSIntegerLiteralNode()
{ }


[[nodiscard]] _ISTD int64 iATSIntegerLiteralNode::get()const noexcept
{
	return this->data;
}

_ISTD Ptr<iATSIntegerLiteralNode> iATSIntegerLiteralNode::set(_ISTD int64 data)
{
	this->data = data;
	return this;
}
