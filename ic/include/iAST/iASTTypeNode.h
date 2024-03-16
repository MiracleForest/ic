/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTTypeNode.h
 * @创建时间:2023.10.01.16:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iASTTypeNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {

        class ICAPI iASTTypeNode : public iASTNode
        {
        public:
            enum class TypeNodeType : int
            {
                keyword,
                identifier
            };

        public:
            TypeNodeType type;
            std::string  value;

        public:
            iASTTypeNode();

            iASTTypeNode(TypeNodeType typeData, std::string valueData);

            ~iASTTypeNode();

        public:
            [[nodiscard]] TypeNodeType getType() const noexcept;
            [[nodiscard]] std::string  getValue() const noexcept;

            Ptr<iASTTypeNode> setType(TypeNodeType typeData);
            Ptr<iASTTypeNode> setValue(std::string valueData);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i