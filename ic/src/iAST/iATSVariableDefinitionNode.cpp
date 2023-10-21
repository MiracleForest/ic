#include "../../include/iAST/iATSVariableDefinitionNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iATSVariableDefinitionNode::iATSVariableDefinitionNode()
	: type(nullptr)
	, name("")
	, value(nullptr)
	, iASTNode(nullptr, iASTNodeType::iATSVariableDefinitionNode, "iATSVariableDefinitionNode", 0, false, {})
{ }

iATSVariableDefinitionNode::iATSVariableDefinitionNode(Ptr<iATSTypeNode> ptype, Ptr<iASTNode> pvalue, CRef<istring> pname)
	: type(ptype)
	, name(pname)
	, value(pvalue)
	, iASTNode(nullptr, iASTNodeType::iATSVariableDefinitionNode, "iATSVariableDefinitionNode", 0, false, {})
{ }

iATSVariableDefinitionNode::~iATSVariableDefinitionNode()
{ }

Ptr<iATSTypeNode> iATSVariableDefinitionNode::getVariableType()const noexcept
{
	return type;
}

iATSVariableDefinitionNode::istring iATSVariableDefinitionNode::getVariableName()const noexcept
{
	return name;
}

Ptr<iASTNode> iATSVariableDefinitionNode::getVariableValue()const noexcept
{
	return value;
}

Ptr<iATSVariableDefinitionNode> iATSVariableDefinitionNode::setVariableType(Ptr<iATSTypeNode> ptype)
{
	this->type = ptype;
	return this;
}

Ptr<iATSVariableDefinitionNode> iATSVariableDefinitionNode::setVariableName(CRef<istring> pname)
{
	this->name = pname;
	return this;
}

Ptr<iATSVariableDefinitionNode> iATSVariableDefinitionNode::setVariableValue(Ptr<iASTNode> pvalue)
{
	this->value = pvalue;
	return this;
}