/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTForStatementNode.h
 * @创建时间:2023.10.21.19:43
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTForStatementNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTCompoundExpressionNode.h"
#include "iASTNode.h"
#include "iATSTypeNode.h"
#include "iATSVariableDefinitionNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class ICAPI iASTForStatementNode : public iASTNode
        {
        public:
            Ptr<iATSVariableDefinitionNode> loopDefineVariable;
            Ptr<iASTCompoundExpressionNode> loopCondition;
            Ptr<iASTNode>                   eachLoopExecute;

        public:
            iASTForStatementNode();

            iASTForStatementNode(
                Ptr<iATSVariableDefinitionNode> ploopDefineVariable,
                Ptr<iASTCompoundExpressionNode> ploopCondition,
                Ptr<iASTNode>                   peachLoopExecute
            );

            ~iASTForStatementNode();

        public:
            [[nodiscard]] Ptr<iATSVariableDefinitionNode> getLoopDefineVariable() const noexcept;
            [[nodiscard]] Ptr<iASTCompoundExpressionNode> getLoopCondition() const noexcept;
            [[nodiscard]] Ptr<iASTNode>                   getEachLoopExecute() const noexcept;

            Ptr<iASTForStatementNode> getLoopsDefineVariable(
                Ptr<iATSVariableDefinitionNode> ploopDefineVariable
            );
            Ptr<iASTForStatementNode> getLoopCondition(Ptr<iASTCompoundExpressionNode> ploopCondition);
            Ptr<iASTForStatementNode> getEachLoopExecute(Ptr<iASTNode> peachLoopExecute);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i