#include "../../include/iAST/iATSFloatingLiteralNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iATSFloatingLiteralNode::iATSFloatingLiteralNode()
	:data(.0)
{ }

iATSFloatingLiteralNode::iATSFloatingLiteralNode(double data)
	:data(data)
{ }

iATSFloatingLiteralNode::~iATSFloatingLiteralNode()
{ }


auto iATSFloatingLiteralNode::get()const noexcept->double
{
	return this->data;
}

_ISTD Ptr<iATSFloatingLiteralNode> iATSFloatingLiteralNode::set(double data)
{
	this->data = data;
	return this;
}
