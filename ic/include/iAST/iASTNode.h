/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iParser.h
 * @创建时间:2022.7.1.22:26
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        enum class iASTNodeType : int
        {
            iASTNode,
            iASTGlobalAreaNode,
            iASTStringLiteralNode,
            iATSFloatingLiteralNode,
            iATSIntegerLiteralNode,
            iATSBinaryOperatorNode,
            iATSTernaryOperatorNode,
            iATSUnaryOperatorNode,
            iATSTypeNode,
            iATSReturnStatementNode,
            iATSVariableDefinitionNode,
            iASTImportStatementNode,
            iASTCompoundExpressionNode,
            iASTForStatementNode
        };


        class ICAPI iASTNode
        {
        public:
            Ptr<iASTNode> parent;

            iASTNodeType type;

            std::string name;

            int line;

            bool additionalNode;

            std::vector<std::string> tags;

        private:
        public:

            virtual Ptr<iASTNode> setAdditionalNode()
            {
                additionalNode = true;
                return this;
            }

        public:
        public:
            virtual Ptr<iASTNode> addTag(CRef<std::string> tag);

            virtual bool hasTag(CRef<std::string> tag) const;

            virtual int getTagIndex(CRef<std::string> tag) const;

            virtual bool removeTag(CRef<std::string> tag);

            virtual std::vector<std::string> getAllTag() const;

        public:
            iASTNode();

            iASTNode(
                Ptr<iASTNode>            parent,
                iASTNodeType             type,
                CRef<std::string>        name,
                int                      line,
                bool                     additionalNode,
                std::vector<std::string> tags
            );

            virtual ~iASTNode();
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i