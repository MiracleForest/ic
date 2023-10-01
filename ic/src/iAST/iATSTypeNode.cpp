#include "../../include/iAST/iATSTypeNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iATSTypeNode::iATSTypeNode()
	:type(TypeNodeType::identifier)
	, value("")
	, iASTNode(nullptr, iASTNodeType::iATSTypeNode, "iATSTypeNode", 0, false, {})
{ }

iATSTypeNode::iATSTypeNode(TypeNodeType typeData, istring valueData)
	:type(typeData)
	, value(valueData)
	, iASTNode(nullptr, iASTNodeType::iATSTypeNode, "iATSTypeNode", 0, false, {})
{ }

iATSTypeNode::~iATSTypeNode()
{
	_ISTD basic::iBasic<iASTNode>::destroy(parent);
}

iATSTypeNode::TypeNodeType iATSTypeNode::getType()const noexcept
{
	return this->type;
}

_ISTDTEXT istring iATSTypeNode::getValue()const noexcept
{
	return this->value;
}

_ISTD Ptr<iATSTypeNode> iATSTypeNode::setType(iATSTypeNode::TypeNodeType typeData)
{
	this->type = typeData;
	return this;
}

_ISTD Ptr<iATSTypeNode> iATSTypeNode::setValue(istring valueData)
{
	this->value = valueData;
	return this;
}