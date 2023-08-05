#include "../../include/iAST/iATSFloatingLiteralNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iATSFloatingLiteralNode::iATSFloatingLiteralNode()
	:_data(.0)
{ }

iATSFloatingLiteralNode::iATSFloatingLiteralNode(double data)
	:_data(data)
{ }

iATSFloatingLiteralNode::~iATSFloatingLiteralNode()
{ }


[[nodiscard]] auto iATSFloatingLiteralNode::get()const noexcept->double
{
	return _data;
}

_ISTD Ptr<iATSFloatingLiteralNode> iATSFloatingLiteralNode::set(double data)
{
	_data = data;
	return this;
}
