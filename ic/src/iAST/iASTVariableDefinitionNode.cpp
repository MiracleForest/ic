#include "../../include/iAST/iASTVariableDefinitionNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTVariableDefinitionNode::iASTVariableDefinitionNode()
    : type(nullptr)
    , name("")
    , value(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTVariableDefinitionNode, "iASTVariableDefinitionNode", 0, false, {})
{
}

iASTVariableDefinitionNode::iASTVariableDefinitionNode(
    Ptr<iASTTypeNode> ptype,
    Ptr<iASTNode>     pvalue,
    CRef<std::string>     pname
)
    : type(ptype)
    , name(pname)
    , value(pvalue)
    , iASTNode(nullptr, iASTNodeType::iASTVariableDefinitionNode, "iASTVariableDefinitionNode", 0, false, {})
{
}

iASTVariableDefinitionNode::~iASTVariableDefinitionNode() {}

Ptr<iASTTypeNode> iASTVariableDefinitionNode::getVariableType() const noexcept { return type; }

std::string iASTVariableDefinitionNode::getVariableName() const noexcept
{
    return name;
}

Ptr<iASTNode> iASTVariableDefinitionNode::getVariableValue() const noexcept { return value; }

Ptr<iASTVariableDefinitionNode> iASTVariableDefinitionNode::setVariableType(Ptr<iASTTypeNode> ptype)
{
    this->type = ptype;
    return this;
}

Ptr<iASTVariableDefinitionNode> iASTVariableDefinitionNode::setVariableName(CRef<std::string> pname)
{
    this->name = pname;
    return this;
}

Ptr<iASTVariableDefinitionNode> iASTVariableDefinitionNode::setVariableValue(Ptr<iASTNode> pvalue)
{
    this->value = pvalue;
    return this;
}