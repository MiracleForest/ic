/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSVariableDefinitionNode.h
 * @创建时间:2023.10.21.16:54
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iATSVariableDefinitionNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include "iATSTypeNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class ICAPI iATSVariableDefinitionNode : public iASTNode
        {
        public:
            Ptr<iATSTypeNode> type;
            Ptr<iASTNode>     value;

            std::string name;

        public:
            iATSVariableDefinitionNode();

            iATSVariableDefinitionNode(
                Ptr<iATSTypeNode> ptype,
                Ptr<iASTNode>     pvalue,
                CRef<std::string> pname
            );

            ~iATSVariableDefinitionNode();

        public:
            [[nodiscard]] Ptr<iATSTypeNode> getVariableType() const noexcept;
            [[nodiscard]] std::string       getVariableName() const noexcept;
            [[nodiscard]] Ptr<iASTNode>     getVariableValue() const noexcept;

            Ptr<iATSVariableDefinitionNode> setVariableType(Ptr<iATSTypeNode> ptype);
            Ptr<iATSVariableDefinitionNode> setVariableName(CRef<std::string> pname);
            Ptr<iATSVariableDefinitionNode> setVariableValue(Ptr<iASTNode> pvalue);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i