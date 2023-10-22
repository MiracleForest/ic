#include "../../include/iAST/iASTForStatementNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iASTForStatementNode::iASTForStatementNode()
    : loopDefineVariable(nullptr)
    , loopCondition(nullptr)
    , eachLoopExecute(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTForStatementNode, "iASTForStatementNode", 0, false, {})
{ }

iASTForStatementNode::iASTForStatementNode(Ptr<iATSVariableDefinitionNode> ploopDefineVariable, Ptr<iASTCompoundExpressionNode> ploopCondition, Ptr<iASTNode> peachLoopExecute)
    : loopDefineVariable(ploopDefineVariable)
    , loopCondition(ploopCondition)
    , eachLoopExecute(peachLoopExecute)
    , iASTNode(nullptr, iASTNodeType::iASTForStatementNode, "iASTForStatementNode", 0, false, {})
{ }

iASTForStatementNode::~iASTForStatementNode()
{ }

_ISTD Ptr<iATSVariableDefinitionNode> iASTForStatementNode::getLoopDefineVariable()const noexcept
{
    return this->loopDefineVariable;
}

_ISTD Ptr<iASTCompoundExpressionNode> iASTForStatementNode::getLoopCondition()const noexcept
{
    return this->loopCondition;
}

_ISTD Ptr<iASTNode> iASTForStatementNode::getEachLoopExecute()const noexcept
{
    return this->eachLoopExecute;
}

_ISTD Ptr<iASTForStatementNode> iASTForStatementNode::getLoopsDefineVariable(_ISTD Ptr<iATSVariableDefinitionNode> ploopDefineVariable)
{
    this->loopDefineVariable = ploopDefineVariable;
    return this;
}

_ISTD Ptr<iASTForStatementNode> iASTForStatementNode::getLoopCondition(_ISTD Ptr<iASTCompoundExpressionNode> ploopCondition)
{
    this->loopCondition = ploopCondition;
    return this;
}

_ISTD Ptr<iASTForStatementNode> iASTForStatementNode::getEachLoopExecute(_ISTD Ptr<iASTNode> peachLoopExecute)
{
    this->eachLoopExecute = peachLoopExecute;
    return this;
}
