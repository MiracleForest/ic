#include "../../include/iAST/iASTForStatementNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTForStatementNode::iASTForStatementNode()
    : loopDefineVariable(nullptr)
    , loopCondition(nullptr)
    , eachLoopExecute(nullptr)
    , iASTNode(nullptr, iASTNodeType::iASTForStatementNode, "iASTForStatementNode", 0, false, {})
{
}

iASTForStatementNode::iASTForStatementNode(
    Ptr<iASTVariableDefinitionNode> ploopDefineVariable,
    Ptr<iASTCompoundExpressionNode> ploopCondition,
    Ptr<iASTNode>                   peachLoopExecute
)
    : loopDefineVariable(ploopDefineVariable)
    , loopCondition(ploopCondition)
    , eachLoopExecute(peachLoopExecute)
    , iASTNode(nullptr, iASTNodeType::iASTForStatementNode, "iASTForStatementNode", 0, false, {})
{
}

iASTForStatementNode::~iASTForStatementNode() {}

Ptr<iASTVariableDefinitionNode> iASTForStatementNode::getLoopDefineVariable() const noexcept
{
    return this->loopDefineVariable;
}

Ptr<iASTCompoundExpressionNode> iASTForStatementNode::getLoopCondition() const noexcept
{
    return this->loopCondition;
}

Ptr<iASTNode> iASTForStatementNode::getEachLoopExecute() const noexcept { return this->eachLoopExecute; }

Ptr<iASTForStatementNode> iASTForStatementNode::getLoopsDefineVariable(
    Ptr<iASTVariableDefinitionNode> ploopDefineVariable
)
{
    this->loopDefineVariable = ploopDefineVariable;
    return this;
}

Ptr<iASTForStatementNode> iASTForStatementNode::getLoopCondition(
    Ptr<iASTCompoundExpressionNode> ploopCondition
)
{
    this->loopCondition = ploopCondition;
    return this;
}

Ptr<iASTForStatementNode> iASTForStatementNode::getEachLoopExecute(Ptr<iASTNode> peachLoopExecute)
{
    this->eachLoopExecute = peachLoopExecute;
    return this;
}
