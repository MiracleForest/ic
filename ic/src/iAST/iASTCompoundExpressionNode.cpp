#include "../../include/iAST/iASTCompoundExpressionNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iASTCompoundExpressionNode::iASTCompoundExpressionNode()
    : expression(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTCompoundExpressionNode, "iASTCompoundExpressionNode", 0, false, {})
{ }

iASTCompoundExpressionNode::iASTCompoundExpressionNode(Ptr<iASTNode> pexpression)
    : expression(pexpression)
    , iASTNode(nullptr, iASTNodeType::iASTCompoundExpressionNode, "iASTCompoundExpressionNode", 0, false, {})
{ }

iASTCompoundExpressionNode::~iASTCompoundExpressionNode()
{ }


Ptr<iASTNode> iASTCompoundExpressionNode::getExpression()const noexcept
{
    return this->expression;
}

Ptr<iASTCompoundExpressionNode> iASTCompoundExpressionNode::setExpression(Ptr<iASTNode> pexpression)
{
    this->expression = pexpression;
    return this;
}
