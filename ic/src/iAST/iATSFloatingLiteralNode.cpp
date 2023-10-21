#include "../../include/iAST/iATSFloatingLiteralNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iATSFloatingLiteralNode::iATSFloatingLiteralNode()
	:data(.0)
	, iASTNode(nullptr, iASTNodeType::iATSFloatingLiteralNode, "iATSFloatingLiteralNode", 0, false, {})
{ }

iATSFloatingLiteralNode::iATSFloatingLiteralNode(double data)
	:data(data)
	, iASTNode(nullptr, iASTNodeType::iATSFloatingLiteralNode, "iATSFloatingLiteralNode", 0, false, {})
{ }

iATSFloatingLiteralNode::~iATSFloatingLiteralNode()
{ }


auto iATSFloatingLiteralNode::get()const noexcept->double
{
	return this->data;
}

Ptr<iATSFloatingLiteralNode> iATSFloatingLiteralNode::set(double data)
{
	this->data = data;
	return this;
}
