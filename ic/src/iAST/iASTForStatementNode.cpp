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

Ptr<iASTNode> iASTForStatementNode::getLoopsDefineVariable()const noexcept
{
    return this->loopDefineVariable;
}

Ptr<iASTNode> iASTForStatementNode::getLoopCondition()const noexcept
{
    return this->loopCondition;
}

Ptr<iASTNode> iASTForStatementNode::getEachLoopExecute()const noexcept
{
    return this->eachLoopExecute;
}

Ptr<iASTForStatementNode> iASTForStatementNode::getLoopsDefineVariable(Ptr<iASTNode> ploopDefineVariable)
{
    this->loopDefineVariable = ploopDefineVariable;
    return this;
}

Ptr<iASTForStatementNode> iASTForStatementNode::getLoopCondition(Ptr<iASTNode> ploopCondition)
{
    this->loopCondition = ploopCondition;
    return this;
}

Ptr<iASTForStatementNode> iASTForStatementNode::getEachLoopExecute(Ptr<iASTNode> peachLoopExecute)
{
    this->eachLoopExecute = peachLoopExecute;
    return this;
}
