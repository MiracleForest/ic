#include "../../include/iAST/iASTTypeNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTTypeNode::iASTTypeNode()
    : type(TypeNodeType::identifier)
    , value("")
    , iASTNode(nullptr, iASTNodeType::iASTTypeNode, "iASTTypeNode", 0, false, {})
{
}

iASTTypeNode::iASTTypeNode(TypeNodeType typeData, std::string valueData)
    : type(typeData)
    , value(valueData)
    , iASTNode(nullptr, iASTNodeType::iASTTypeNode, "iASTTypeNode", 0, false, {})
{
}

iASTTypeNode::~iASTTypeNode()
{
    // delete parent;
}

iASTTypeNode::TypeNodeType iASTTypeNode::getType() const noexcept { return this->type; }

std::string iASTTypeNode::getValue() const noexcept { return this->value; }

Ptr<iASTTypeNode> iASTTypeNode::setType(iASTTypeNode::TypeNodeType typeData)
{
    this->type = typeData;
    return this;
}

Ptr<iASTTypeNode> iASTTypeNode::setValue(std::string valueData)
{
    this->value = valueData;
    return this;
}