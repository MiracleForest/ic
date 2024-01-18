/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSTypeNode.h
 * @创建时间:2023.10.01.16:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iATSTypeNode
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

        class ICAPI iATSTypeNode : public iASTNode
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
            iATSTypeNode();

            iATSTypeNode(TypeNodeType typeData, std::string valueData);

            ~iATSTypeNode();

        public:
            [[nodiscard]] TypeNodeType getType() const noexcept;
            [[nodiscard]] std::string  getValue() const noexcept;

            Ptr<iATSTypeNode> setType(TypeNodeType typeData);
            Ptr<iATSTypeNode> setValue(std::string valueData);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i