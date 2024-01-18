#include "../../include/iAST/iATSTypeNode.h"
using namespace MiracleForest::i::icFamily::AST;


iATSTypeNode::iATSTypeNode()
    : type(TypeNodeType::identifier)
    , value("")
    , iASTNode(nullptr, iASTNodeType::iATSTypeNode, "iATSTypeNode", 0, false, {})
{
}

iATSTypeNode::iATSTypeNode(TypeNodeType typeData, std::string valueData)
    : type(typeData)
    , value(valueData)
    , iASTNode(nullptr, iASTNodeType::iATSTypeNode, "iATSTypeNode", 0, false, {})
{
}

iATSTypeNode::~iATSTypeNode()
{
    // delete parent;
}

iATSTypeNode::TypeNodeType iATSTypeNode::getType() const noexcept { return this->type; }

std::string iATSTypeNode::getValue() const noexcept { return this->value; }

Ptr<iATSTypeNode> iATSTypeNode::setType(iATSTypeNode::TypeNodeType typeData)
{
    this->type = typeData;
    return this;
}

Ptr<iATSTypeNode> iATSTypeNode::setValue(std::string valueData)
{
    this->value = valueData;
    return this;
}