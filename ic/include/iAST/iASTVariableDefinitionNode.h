/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTVariableDefinitionNode.h
 * @创建时间:2023.10.21.16:54
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTVariableDefinitionNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include "iASTTypeNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class ICAPI iASTVariableDefinitionNode : public iASTNode
        {
        public:
            Ptr<iASTTypeNode> type;
            Ptr<iASTNode>     value;

            std::string name;

        public:
            iASTVariableDefinitionNode();

            iASTVariableDefinitionNode(
                Ptr<iASTTypeNode> ptype,
                Ptr<iASTNode>     pvalue,
                CRef<std::string> pname
            );

            ~iASTVariableDefinitionNode();

        public:
            [[nodiscard]] Ptr<iASTTypeNode> getVariableType() const noexcept;
            [[nodiscard]] std::string       getVariableName() const noexcept;
            [[nodiscard]] Ptr<iASTNode>     getVariableValue() const noexcept;

            Ptr<iASTVariableDefinitionNode> setVariableType(Ptr<iASTTypeNode> ptype);
            Ptr<iASTVariableDefinitionNode> setVariableName(CRef<std::string> pname);
            Ptr<iASTVariableDefinitionNode> setVariableValue(Ptr<iASTNode> pvalue);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i