#include "../../include/iAST/iATSVariableDefinitionNode.h"
using namespace MiracleForest::i::icFamily::AST;


iATSVariableDefinitionNode::iATSVariableDefinitionNode()
    : type(nullptr)
    , name("")
    , value(nullptr)
    , iASTNode(nullptr, iASTNodeType::iATSVariableDefinitionNode, "iATSVariableDefinitionNode", 0, false, {})
{
}

iATSVariableDefinitionNode::iATSVariableDefinitionNode(
    Ptr<iATSTypeNode> ptype,
    Ptr<iASTNode>     pvalue,
    CRef<std::string>     pname
)
    : type(ptype)
    , name(pname)
    , value(pvalue)
    , iASTNode(nullptr, iASTNodeType::iATSVariableDefinitionNode, "iATSVariableDefinitionNode", 0, false, {})
{
}

iATSVariableDefinitionNode::~iATSVariableDefinitionNode() {}

Ptr<iATSTypeNode> iATSVariableDefinitionNode::getVariableType() const noexcept { return type; }

std::string iATSVariableDefinitionNode::getVariableName() const noexcept
{
    return name;
}

Ptr<iASTNode> iATSVariableDefinitionNode::getVariableValue() const noexcept { return value; }

Ptr<iATSVariableDefinitionNode> iATSVariableDefinitionNode::setVariableType(Ptr<iATSTypeNode> ptype)
{
    this->type = ptype;
    return this;
}

Ptr<iATSVariableDefinitionNode> iATSVariableDefinitionNode::setVariableName(CRef<std::string> pname)
{
    this->name = pname;
    return this;
}

Ptr<iATSVariableDefinitionNode> iATSVariableDefinitionNode::setVariableValue(Ptr<iASTNode> pvalue)
{
    this->value = pvalue;
    return this;
}